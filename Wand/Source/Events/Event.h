#pragma once

namespace wand
{
	enum class EventCategory
	{
		Window, Input
	};

	enum class EventType
	{
		WindowResize,
		KeyUp, KeyDown, MouseButtonUp, MouseButtonDown,
		MouseScrollX, MouseScrollY, MouseMove
	};

	class Event
	{
	protected:
		Event(EventCategory category, EventType type);
	public:
		EventCategory GetCategory() const;
		EventType GetType() const;
	private:
		EventCategory mCategory;
		EventType mType;
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height);
		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
	private:
		unsigned int mWidth;
		unsigned int mHeight;
	};

	class KeyDownEvent : public Event
	{
	public:
		KeyDownEvent(int key, bool isCapital);
		int GetKey() const;
		bool IsCapital() const;
	private:
		int mKey;
		bool mIsCapital;
	};

	class KeyUpEvent : public Event
	{
	public:
		KeyUpEvent(int key, bool isCapital);
		int GetKey() const;
		bool IsCapital() const;
	private:
		int mKey;
		bool mIsCapital;
	};

	class MouseButtonDownEvent : public Event
	{
	public:
		MouseButtonDownEvent(int button);
		int GetButton() const;
	private:
		int mButton;
	};

	class MouseButtonUpEvent : public Event
	{
	public:
		MouseButtonUpEvent(int button);
		int GetButton() const;
	private:
		int mButton;
	};

	class MouseScrollXEvent : public Event
	{
	public:
		MouseScrollXEvent(double offset);
		double GetOffset() const;
	private:
		double mOffset;
	};

	class MouseScrollYEvent : public Event
	{
	public:
		MouseScrollYEvent(double offset);
		double GetOffset() const;
	private:
		double mOffset;
	};

	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(double xPos, double yPos);
		double GetXPos() const;
		double GetYPos() const;
	private:
		double mXPos;
		double mYPos;
	};
}
