#pragma once

#include "Events/Event.h"
#include "InputMacros.h"

namespace wand
{
	class Input
	{
	public:
		Input();

		int GetX() const;
		int GetY() const;
		bool KeyDown(int key) const;
		bool KeyUp(int key) const;
		bool MouseButtonDown(int button) const;
		bool MouseButtonUp(int button) const;
		bool ScrollX() const;
		bool ScrollY() const;
		float GetScrollX() const;
		float GetScrollY() const;

		void ClearEvents();
		void AddEvent(Event* event);
		void SetMousePos(double xPos, double yPos);

	private:
		std::vector<Event*> mEvents;
		double mXPos;
		double mYPos;
	};
}