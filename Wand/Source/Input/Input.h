#pragma once

#include "Events/Event.h"
#include "InputMacros.h"

namespace wand
{
	class Input
	{
	public:
		Input();

		/* Search this frame's events for a specific type of input */
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

		// Clear the last frame's events
		void ClearEvents();
		// Add a new event for this frame
		void AddEvent(Event* event);
		// Set the latest mouse position
		void SetMousePos(double xPos, double yPos);

	private:
		std::vector<Event*> mEvents;
		double mXPos;
		double mYPos;
	};
}