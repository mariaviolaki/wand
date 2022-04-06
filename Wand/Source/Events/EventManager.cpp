#include "WandPCH.h"
#include "EventManager.h"
#include "Input/InputMacros.h"

namespace wand
{
	EventManager::EventManager()
		: mInput(nullptr), mXPos(0.0), mYPos(0.0)
	{}

	void EventManager::Init(Input* input)
	{
		mInput = input;
	}

	void EventManager::Update(std::vector<std::unique_ptr<UIEntity>>& entities)
	{
		// Clear the events of the last frame
		mInput->ClearEvents();
		mEvents.clear();
		// Clear the entities of the last frame
		mEntities.clear();
		// Only use the entities which are visible and enabled
		for (const auto& entity : entities)
		{
			if (entity->IsVisible() && entity->IsEnabled())
				mEntities.emplace_back(entity.get());
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
	{}

	void EventManager::HandleInputEvent(Event* inputEvent)
	{
		// Push the correct event to the event buffer
		switch (inputEvent->GetType())
		{
		case EventType::KeyDown:
			mEvents.emplace_back(
				std::unique_ptr<KeyDownEvent>(static_cast<KeyDownEvent*>(inputEvent)));
			break;
		case EventType::KeyUp:
			mEvents.emplace_back(
				std::unique_ptr<KeyUpEvent>(static_cast<KeyUpEvent*>(inputEvent)));
			break;
		case EventType::MouseButtonDown:
			mEvents.emplace_back(
				std::unique_ptr<MouseButtonDownEvent>(static_cast<MouseButtonDownEvent*>(inputEvent)));
			break;
		case EventType::MouseButtonUp:
			mEvents.emplace_back(
				std::unique_ptr<MouseButtonUpEvent>(static_cast<MouseButtonUpEvent*>(inputEvent)));
			ProcessLeftClick(static_cast<MouseButtonUpEvent*>(inputEvent));
			break;
		case EventType::MouseScrollX:
			mEvents.emplace_back(
				std::unique_ptr<MouseScrollXEvent>(static_cast<MouseScrollXEvent*>(inputEvent)));
			break;
		case EventType::MouseScrollY:
			mEvents.emplace_back(
				std::unique_ptr<MouseScrollYEvent>(static_cast<MouseScrollYEvent*>(inputEvent)));
			break;
		case EventType::MouseMove:
			mEvents.emplace_back(
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

	void EventManager::ProcessLeftClick(MouseButtonUpEvent* event)
	{
		if (mEntities.empty() || event->GetButton() != MOUSE_BUTTON_LEFT)
			return;

		// Add the entities in the current mouse position to one vector
		std::vector<UIEntity*> validEntities;
		for (auto& entity : mEntities)
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
