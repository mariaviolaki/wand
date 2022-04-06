#include "WandPCH.h"
#include "Input.h"

namespace wand
{
    void Input::ClearEvents()
    {
        mEvents.clear();
    }

    void Input::AddEvent(Event* event)
    {
        mEvents.emplace_back(event);
    }

    void Input::SetMousePos(double xPos, double yPos)
    {
        mXPos = xPos;
        mYPos = yPos;
    }
}