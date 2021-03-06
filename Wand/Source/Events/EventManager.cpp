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
		if (windowEvent->GetType() == EventType::WindowResize)
		{
			std::unique_ptr<WindowResizeEvent> event(static_cast<WindowResizeEvent*>(windowEvent));
			ProcessWindowResize(static_cast<WindowResizeEvent*>(event.get()));
		}
		else if (windowEvent->GetType() == EventType::WindowClose)
		{
			std::unique_ptr<WindowCloseEvent> event(static_cast<WindowCloseEvent*>(windowEvent));
			mWindow->RunCloseFunctions();
		}
	}

	void EventManager::HandleInputEvent(Event* inputEvent)
	{
		// Don't process the event twice
		if (ProcessUIEvent(inputEvent))
			return;

		// Save the position of the mouse in case it doesn't move in the next frame
		if (inputEvent->GetType() == EventType::MouseMove)
		{
			mXPos = static_cast<MouseMoveEvent*>(inputEvent)->GetXPos();
			mYPos = static_cast<MouseMoveEvent*>(inputEvent)->GetYPos();
			mInput->SetMousePos(mXPos, mYPos);
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
		ResizeEntities(scale);
	}

	bool EventManager::ProcessUIEvent(Event* event)
	{
		// Do nothing if there are no enabled entities
		if (mActiveEntities.empty())
		{
			mCursorManager->SetCursor(CursorType::ARROW);
			return false;
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
			return false;
		}

		// Switch to the hand cursor because there are enabled entities in this position
		mCursorManager->SetCursor(CursorType::HAND);

		// Run the function of the entity in front of the others
		SortEntities(validEntities);
		return ProcessUIFunction(validEntities[0], event);
	}

	bool EventManager::ProcessUIFunction(UIEntity* entity, Event* event)
	{
		std::function<void()> function;

		// Get the appropriate function
		if (event->GetType() == EventType::MouseButtonRelease)
		{
			if (static_cast<MouseButtonReleaseEvent*>(event)->GetButton() == MOUSE_BUTTON_LEFT)
				function = entity->GetLeftClickFunction();
			else if (static_cast<MouseButtonReleaseEvent*>(event)->GetButton() == MOUSE_BUTTON_RIGHT)
				function = entity->GetRightClickFunction();
		}
		else
		{
			function = entity->GetHoverFunction();
		}

		// Run the function if there is one set
		if (!function)
			return false;
		function();
		return true;
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

	void EventManager::ResizeEntities(glm::vec2 scale)
	{
		// Resize the objects drawn to the window
		for (auto& entity : mEntities)
		{
			entity->GetTransform()->SetScale(scale.x, scale.y);
			if (dynamic_cast<TextBox*>(entity))
			{
				auto text = static_cast<TextGFX*>(entity->GetDrawable());
				text->SetFont(text->GetFontName(), scale.x * text->GetStartFontSize());
			}
			else if (dynamic_cast<Button*>(entity))
			{
				auto text = static_cast<TextGFX*>(static_cast<Button*>(entity)->GetTextDrawable());
				text->SetFont(text->GetFontName(), scale.x * text->GetStartFontSize());
			}
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
