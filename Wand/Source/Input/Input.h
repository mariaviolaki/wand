#pragma once

#include "Events/Event.h"

namespace wand
{
	class Input
	{
	public:
		void ClearEvents();
		void AddEvent(Event* event);
		void SetMousePos(double xPos, double yPos);

	private:
		std::vector<Event*> mEvents;
		double mXPos;
		double mYPos;
	};
}