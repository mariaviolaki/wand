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
		KeyRelease, KeyPress, MouseButtonRelease, MouseButtonPress,
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

	class KeyPressEvent : public Event
	{
	public:
		KeyPressEvent(int key, bool isCapital);
		int GetKey() const;
		bool IsCapital() const;
	private:
		int mKey;
		bool mIsCapital;
	};

	class KeyReleaseEvent : public Event
	{
	public:
		KeyReleaseEvent(int key, bool isCapital);
		int GetKey() const;
		bool IsCapital() const;
	private:
		int mKey;
		bool mIsCapital;
	};

	class MouseButtonPressEvent : public Event
	{
	public:
		MouseButtonPressEvent(int button);
		int GetButton() const;
	private:
		int mButton;
	};

	class MouseButtonReleaseEvent : public Event
	{
	public:
		MouseButtonReleaseEvent(int button);
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
