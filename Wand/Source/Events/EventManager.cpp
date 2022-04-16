#include "WandPCH.h"
#include "EventManager.h"
#include "Input/InputMacros.h"
#include "glad/glad.h"

namespace wand
{
	EventManager::EventManager()
		: mWindow(nullptr), mInput(nullptr), mRenderer(nullptr), mXPos(0.0), mYPos(0.0)
	{}

	void EventManager::Init(Window* window, Input* input, Renderer* renderer)
	{
		mWindow = window;
		mInput = input;
		mRenderer = renderer;
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
		mVisibleEntities.clear();
		mActiveEntities.clear();
		// Process all entities given by the app
		for (const auto& entity : entities)
		{
			if (entity->IsVisible())
			{
				// Add to the vector of visible entities
				mVisibleEntities.emplace_back(entity.get());
				if (entity->IsEnabled())
				{
					// Add to the vector of visible and enabled entities
					mActiveEntities.emplace_back(entity.get());
				}
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
			ProcessLeftClick(static_cast<MouseButtonUpEvent*>(inputEvent));
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
		for (auto& entity : mVisibleEntities)
			entity->GetTransform().SetScale(scale.x, scale.y);
	}

	void EventManager::ProcessLeftClick(MouseButtonUpEvent* event)
	{
		if (mActiveEntities.empty() || event->GetButton() != MOUSE_BUTTON_LEFT)
			return;

		// Add the entities in the current mouse position to one vector
		std::vector<UIEntity*> validEntities;
		for (auto& entity : mActiveEntities)
		{
			if (IsMouseInArea(entity->GetTransform()))
				validEntities.push_back(entity);
		}

		if (validEntities.empty())
			return;

		// Run the function of the entity in front of the others
		SortEntities(validEntities);
		auto function = validEntities[0]->GetLeftClickFunction();
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

	bool EventManager::IsMouseInArea(const Transform& transform)
	{
		glm::vec2 pos = transform.GetPosition();
		return mXPos >= pos.x && mXPos <= pos.x + transform.GetWidth()
			&& mYPos >= pos.y && mYPos <= pos.y + transform.GetHeight();
	}

	void EventManager::SortEntities(std::vector<UIEntity*>& entities) const
	{
		// Sort entities based on their depth by providing a comparison function
		std::sort(entities.begin(), entities.end(),
		[](const UIEntity* a, const UIEntity* b)
		{
			// Sort in descending order
			return a->GetTransform().GetDepth() > b->GetTransform().GetDepth();
		});
	}
}
