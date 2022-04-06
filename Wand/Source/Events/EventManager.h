#pragma once

#include "Event.h"
#include "UI/UIEntity.h"
#include "Input/Input.h"
#include "Graphics/Base/Transform.h"

namespace wand
{
	class EventManager
	{
	public:
		EventManager();
		void Init(Input* input);
		void Update(std::vector<std::unique_ptr<UIEntity>>& entities);
		void HandleEvent(Event* event);

	private:
		std::vector<std::unique_ptr<Event>> mEvents;
		std::vector<UIEntity*> mEntities;
		Input* mInput;
		double mXPos;
		double mYPos;

		void HandleWindowEvent(Event* windowEvent);
		void HandleInputEvent(Event* inputEvent);
		void ProcessLeftClick(MouseButtonUpEvent* event);
		bool IsMouseInArea(const Transform& transform);
		// Sort entities based on their depth in the window
		void SortEntities(std::vector<UIEntity*>& entities) const;
	};
}
