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
		bool KeyPressed(int key) const;
		bool KeyReleased(int key) const;
		bool MouseButtonPressed(int button) const;
		bool MouseButtonReleased(int button) const;
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
