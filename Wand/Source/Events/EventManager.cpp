#include "WandPCH.h"
#include "EventManager.h"
#include "glad/glad.h"
#include "Input/InputMacros.h"
#include "UI/Button.h"

namespace wand
{
	EventManager::EventManager()
		: mWindow(nullptr), mInput(nullptr), mRenderer(nullptr), mCursorManager(nullptr),
		mXPos(0.0), mYPos(0.0)
	{}

	void EventManager::Init(Window* window, Input* input, Renderer* renderer, CursorManager* cursorManager)
	{
		mWindow = window;
		mInput = input;
		mRenderer = renderer;
		mCursorManager = cursorManager;
	}

	void EventManager::Clear()
	{
		// Clear the events of the last frame
		mInput->ClearEvents();
		mInputEvents.clear();
	}

	void EventManager::SetEntities(std::vector<std::unique_ptr<UIEntity>>& entities)
	{
		// Clear the entities of the last frame
		mEntities.clear();
		mActiveEntities.clear();
		// Process all entities given by the app
		for (const auto& entity : entities)
		{
			// Add to the vector of entities
			mEntities.emplace_back(entity.get());
			if (entity->IsEnabled() && entity->IsVisible())
			{
				// Add to the vector of enabled and visible entities
				mActiveEntities.emplace_back(entity.get());
			}	
		}
	}

	void EventManager::HandleEvent(Event* event)
	{
		switch (event->GetCategory())
		{
		case EventCategory::Window:
			HandleWindowEvent(event);
			break;
		case EventCategory::Input:
			HandleInputEvent(event);
			break;
		}
	}

	void EventManager::HandleWindowEvent(Event* windowEvent)
	{
		switch (windowEvent->GetType())
		{
		case EventType::WindowResize:
			std::unique_ptr<WindowResizeEvent> event(static_cast<WindowResizeEvent*>(windowEvent));
			ProcessWindowResize(static_cast<WindowResizeEvent*>(event.get()));
			break;
		}
	}

	void EventManager::HandleInputEvent(Event* inputEvent)
	{
		// Push the correct event to the event buffer
		switch (inputEvent->GetType())
		{
		case EventType::KeyDown:
			mInputEvents.emplace_back(
				std::unique_ptr<KeyDownEvent>(static_cast<KeyDownEvent*>(inputEvent)));
			break;
		case EventType::KeyUp:
			mInputEvents.emplace_back(
				std::unique_ptr<KeyUpEvent>(static_cast<KeyUpEvent*>(inputEvent)));
			break;
		case EventType::MouseButtonDown:
			mInputEvents.emplace_back(
				std::unique_ptr<MouseButtonDownEvent>(static_cast<MouseButtonDownEvent*>(inputEvent)));
			break;
		case EventType::MouseButtonUp:
			mInputEvents.emplace_back(
				std::unique_ptr<MouseButtonUpEvent>(static_cast<MouseButtonUpEvent*>(inputEvent)));
			break;
		case EventType::MouseScrollX:
			mInputEvents.emplace_back(
				std::unique_ptr<MouseScrollXEvent>(static_cast<MouseScrollXEvent*>(inputEvent)));
			break;
		case EventType::MouseScrollY:
			mInputEvents.emplace_back(
				std::unique_ptr<MouseScrollYEvent>(static_cast<MouseScrollYEvent*>(inputEvent)));
			break;
		case EventType::MouseMove:
			mInputEvents.emplace_back(
				std::unique_ptr<MouseMoveEvent>(static_cast<MouseMoveEvent*>(inputEvent)));
			// Save the position of the mouse in case it doesn't move in the next frame
			mXPos = static_cast<MouseMoveEvent*>(inputEvent)->GetXPos();
			mYPos = static_cast<MouseMoveEvent*>(inputEvent)->GetYPos();
			mInput->SetMousePos(mXPos, mYPos);
			break;
		}
		ProcessUIEvent(inputEvent);
		// Send the event to the Input class
		mInput->AddEvent(inputEvent);
	}

	void EventManager::ProcessWindowResize(WindowResizeEvent* event)
	{
		// Reset the rendering area
		glm::vec2 pos({ 0.0f, 0.0f });
		glm::vec2 dimens({ 0.0f, 0.0f });
		ResetWindowBounds(event, pos, dimens);
		glViewport(pos.x, pos.y, dimens.x, dimens.y);
		// Change the old dimensions saved in the window
		mWindow->SetWidth(dimens.x);
		mWindow->SetHeight(dimens.y);
		// Save the change of the width and height
		glm::vec2 scale({ 0.0f, 0.0f });
		scale.x = dimens.x / mWindow->GetStartWidth();
		scale.y = dimens.y / mWindow->GetStartHeight();
		// Reset the projection matrix in the renderer
		mRenderer->ResetProjectionMatrix(0, 0, dimens.x, dimens.y);
		// Resize the objects drawn to the window
		for (auto& entity : mEntities)
			entity->GetTransform()->SetScale(scale.x, scale.y);
	}

	void EventManager::ProcessUIEvent(Event* event)
	{
		// Do nothing if there are no enabled entities
		if (mActiveEntities.empty())
		{
			mCursorManager->SetCursor(CursorType::ARROW);
			return;
		}

		// Add the entities in the current mouse position to one vector
		std::vector<UIEntity*> validEntities;
		for (auto& entity : mActiveEntities)
		{
			if (IsMouseInArea(entity->GetTransform()))
				validEntities.push_back(entity);
		}

		// Do nothing if there are no entities in the current mouse position
		if (validEntities.empty())
		{
			mCursorManager->SetCursor(CursorType::ARROW);
			return;
		}

		// Switch to the hand cursor because there are enabled entities in this position
		mCursorManager->SetCursor(CursorType::HAND);

		// Run the function of the entity in front of the others
		SortEntities(validEntities);
		ProcessUIFunction(validEntities[0], event);
	}

	void EventManager::ProcessUIFunction(UIEntity* entity, Event* event)
	{
		std::function<void()> function;

		// Get the appropriate function
		if (event->GetType() == EventType::MouseButtonUp)
		{
			if (static_cast<MouseButtonUpEvent*>(event)->GetButton() == MOUSE_BUTTON_LEFT)
				function = entity->GetLeftClickFunction();
			else if (static_cast<MouseButtonUpEvent*>(event)->GetButton() == MOUSE_BUTTON_RIGHT)
				function = entity->GetRightClickFunction();
		}
		else
		{
			function = entity->GetHoverFunction();
		}

		// Run the function if there is one set
		if (function)
			function();
	}

	void EventManager::ResetWindowBounds(WindowResizeEvent* event, glm::vec2& pos, glm::vec2& dimens)
	{
		// Keep the dimension that changed the least
		if (event->GetWidth() - mWindow->GetWidth() >= event->GetHeight() - mWindow->GetHeight())
		{
			dimens.y = event->GetHeight();
			dimens.x = event->GetHeight() * (mWindow->GetAspectRatio().x / mWindow->GetAspectRatio().y);
			pos.y = 0;
			pos.x = (event->GetWidth() - dimens.x) / 2;
		}
		else
		{
			dimens.x = event->GetWidth();
			dimens.y = event->GetWidth() * (mWindow->GetAspectRatio().y / mWindow->GetAspectRatio().x);
			pos.x = 0;
			pos.y = (event->GetHeight() - dimens.y) / 2;
		}
	}

	bool EventManager::IsMouseInArea(Transform* transform)
	{
		Vector2 pos = transform->GetPos();
		Vector2 scale = transform->GetScale();
		return mXPos >= pos.x * scale.x && mXPos <= (pos.x + transform->GetWidth()) * scale.x
			&& mYPos >= pos.y * scale.y && mYPos <= (pos.y + transform->GetHeight()) * scale.y;
	}

	void EventManager::SortEntities(std::vector<UIEntity*>& entities) const
	{
		// Sort entities based on their depth by providing a comparison function
		std::sort(entities.begin(), entities.end(),
		[](const UIEntity* a, const UIEntity* b)
		{
			// Sort in descending order
			return a->GetTransform()->GetLayer() > b->GetTransform()->GetLayer();
		});
	}
}
