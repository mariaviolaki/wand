#include "WandPCH.h"
#include "Input.h"

namespace wand
{
    Input::Input()
        : mXPos(0.0), mYPos(0.0)
    {}

    int Input::GetX() const { return mXPos; }
    int Input::GetY() const { return mYPos; }

    bool Input::KeyDown(int key) const
    {
        for (const auto& event : mEvents)
        {
            if (event->GetType() == EventType::KeyDown)
                if (static_cast<KeyDownEvent*>(event)->GetKey() == key)
                    return true;
        }
        return false;
    }

    bool Input::KeyUp(int key) const
    {
        for (const auto& event : mEvents)
        {
            if (event->GetType() == EventType::KeyUp)
                if (static_cast<KeyUpEvent*>(event)->GetKey() == key)
                    return true;
        }
        return false;
    }

    bool Input::MouseButtonDown(int button) const
    {
        for (const auto& event : mEvents)
        {
            if (event->GetType() == EventType::MouseButtonDown)
                if (static_cast<MouseButtonDownEvent*>(event)->GetButton() == button)
                    return true;
        }
        return false;
    }

    bool Input::MouseButtonUp(int button) const
    {
        for (const auto& event : mEvents)
        {
            if (event->GetType() == EventType::MouseButtonUp)
                if (static_cast<MouseButtonUpEvent*>(event)->GetButton() == button)
                    return true;
        }
        return false;
    }

    bool Input::ScrollX() const
    {
        for (const auto& event : mEvents)
        {
            if (event->GetType() == EventType::MouseScrollX)
                return true;
        }
        return false;
    }

    bool Input::ScrollY() const
    {
        for (const auto& event : mEvents)
        {
            if (event->GetType() == EventType::MouseScrollY)
                return true;
        }
        return false;
    }

    float Input::GetScrollX() const
    {
        for (const auto& event : mEvents)
        {
            if (event->GetType() == EventType::MouseScrollX)
                return static_cast<MouseScrollXEvent*>(event)->GetOffset();
        }
        return 0.0f;
    }

    float Input::GetScrollY() const
    {
        for (const auto& event : mEvents)
        {
            if (event->GetType() == EventType::MouseScrollY)
                return static_cast<MouseScrollYEvent*>(event)->GetOffset();
        }
        return 0.0f;
    }

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