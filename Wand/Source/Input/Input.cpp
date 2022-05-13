#include "WandPCH.h"
#include "Input.h"

namespace wand
{
    Input::Input()
        : mXPos(0.0), mYPos(0.0), mEvents()
    {}

    int Input::GetX() const { return mXPos; }
    int Input::GetY() const { return mYPos; }

    bool Input::MouseMoved() const
    {
        for (const auto& event : mEvents)
        {
            if (event->GetType() == EventType::MouseMove)
                return true;
        }
        return false;
    }

    bool Input::KeyPressed(int key) const
    {
        for (const auto& event : mEvents)
        {
            if (event->GetType() == EventType::KeyPress)
                if (static_cast<KeyPressEvent*>(event.get())->GetKey() == key)
                    return true;
        }
        return false;
    }

    bool Input::KeyReleased(int key) const
    {
        for (const auto& event : mEvents)
        {
            if (event->GetType() == EventType::KeyRelease)
                if (static_cast<KeyReleaseEvent*>(event.get())->GetKey() == key)
                    return true;
        }
        return false;
    }

    bool Input::MouseButtonPressed(int button) const
    {
        for (const auto& event : mEvents)
        {
            if (event->GetType() == EventType::MouseButtonPress)
                if (static_cast<MouseButtonPressEvent*>(event.get())->GetButton() == button)
                    return true;
        }
        return false;
    }

    bool Input::MouseButtonReleased(int button) const
    {
        for (const auto& event : mEvents)
        {
            if (event->GetType() == EventType::MouseButtonRelease)
                if (static_cast<MouseButtonReleaseEvent*>(event.get())->GetButton() == button)
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
                return static_cast<MouseScrollXEvent*>(event.get())->GetOffset();
        }
        return 0.0f;
    }

    float Input::GetScrollY() const
    {
        for (const auto& event : mEvents)
        {
            if (event->GetType() == EventType::MouseScrollY)
                return static_cast<MouseScrollYEvent*>(event.get())->GetOffset();
        }
        return 0.0f;
    }

    void Input::ClearEvents() { mEvents.clear(); }

    void Input::AddEvent(Event* event)
    {
        // Push the correct event to the event buffer
        switch (event->GetType())
        {
        case EventType::KeyPress:
            mEvents.emplace_back(
                std::unique_ptr<KeyPressEvent>(static_cast<KeyPressEvent*>(event)));
            break;
        case EventType::KeyRelease:
            mEvents.emplace_back(
                std::unique_ptr<KeyReleaseEvent>(static_cast<KeyReleaseEvent*>(event)));
            break;
        case EventType::MouseButtonPress:
            mEvents.emplace_back(
                std::unique_ptr<MouseButtonPressEvent>(static_cast<MouseButtonPressEvent*>(event)));
            break;
        case EventType::MouseButtonRelease:
            mEvents.emplace_back(
                std::unique_ptr<MouseButtonReleaseEvent>(static_cast<MouseButtonReleaseEvent*>(event)));
            break;
        case EventType::MouseScrollX:
            mEvents.emplace_back(
                std::unique_ptr<MouseScrollXEvent>(static_cast<MouseScrollXEvent*>(event)));
            break;
        case EventType::MouseScrollY:
            mEvents.emplace_back(
                std::unique_ptr<MouseScrollYEvent>(static_cast<MouseScrollYEvent*>(event)));
            break;
        case EventType::MouseMove:
            mEvents.emplace_back(
                std::unique_ptr<MouseMoveEvent>(static_cast<MouseMoveEvent*>(event)));
            break;
        }
    }

    void Input::SetMousePos(double xPos, double yPos)
    {
        mXPos = xPos;
        mYPos = yPos;
    }
}
