#include "WandPCH.h"
#include "Input.h"

namespace wand
{
    Input::Input()
        : mXPos(0.0), mYPos(0.0), mEvents()
    {}

    int Input::GetX() const { return mXPos; }
    int Input::GetY() const { return mYPos; }

    bool Input::KeyPressed(int key) const
    {
        for (const auto& event : mEvents)
        {
            if (event->GetType() == EventType::KeyPress)
                if (static_cast<KeyPressEvent*>(event)->GetKey() == key)
                    return true;
        }
        return false;
    }

    bool Input::KeyReleased(int key) const
    {
        for (const auto& event : mEvents)
        {
            if (event->GetType() == EventType::KeyRelease)
                if (static_cast<KeyReleaseEvent*>(event)->GetKey() == key)
                    return true;
        }
        return false;
    }

    bool Input::MouseButtonPressed(int button) const
    {
        for (const auto& event : mEvents)
        {
            if (event->GetType() == EventType::MouseButtonPress)
                if (static_cast<MouseButtonPressEvent*>(event)->GetButton() == button)
                    return true;
        }
        return false;
    }

    bool Input::MouseButtonReleased(int button) const
    {
        for (const auto& event : mEvents)
        {
            if (event->GetType() == EventType::MouseButtonRelease)
                if (static_cast<MouseButtonReleaseEvent*>(event)->GetButton() == button)
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