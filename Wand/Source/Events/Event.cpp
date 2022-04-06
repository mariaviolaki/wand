#include "WandPCH.h"
#include "Event.h"

namespace wand
{
	/************************* EVENT BASE CLASS ***************************************/
	Event::Event(EventCategory category, EventType type)
		: mCategory(category), mType(type)
	{}
	EventCategory Event::GetCategory() const { return mCategory; }
	EventType Event::GetType() const { return mType; }

	/************************* KEY DOWN EVENT CLASS ***********************************/
	KeyDownEvent::KeyDownEvent(int key, bool isCapital)
		: Event(EventCategory::Input, EventType::KeyDown), mKey(key), mIsCapital(isCapital)
	{}
	int KeyDownEvent::GetKey() const { return mKey; }
	bool KeyDownEvent::IsCapital() const { return mIsCapital; }

	/************************* KEY UP EVENT CLASS *************************************/
	KeyUpEvent::KeyUpEvent(int key, bool isCapital)
		: Event(EventCategory::Input, EventType::KeyUp), mKey(key), mIsCapital(isCapital)
	{}
	int KeyUpEvent::GetKey() const { return mKey; }
	bool KeyUpEvent::IsCapital() const { return mIsCapital; }

	/************************* MOUSE BUTTON DOWN EVENT CLASS **************************/
	MouseButtonDownEvent::MouseButtonDownEvent(int button)
		: Event(EventCategory::Input, EventType::MouseButtonDown), mButton(button)
	{}
	int MouseButtonDownEvent::GetButton() const { return mButton; }

	/************************* MOUSE BUTTON UP EVENT CLASS ****************************/
	MouseButtonUpEvent::MouseButtonUpEvent(int button)
		: Event(EventCategory::Input, EventType::MouseButtonUp), mButton(button)
	{}
	int MouseButtonUpEvent::GetButton() const { return mButton; }

	/************************* MOUSE SCROLL X EVENT CLASS *****************************/
	MouseScrollXEvent::MouseScrollXEvent(double offset)
		: Event(EventCategory::Input, EventType::MouseScrollX), mOffset(offset)
	{}
	double MouseScrollXEvent::GetOffset() const { return mOffset; }

	/************************* MOUSE SCROLL X EVENT CLASS *****************************/
	MouseScrollYEvent::MouseScrollYEvent(double offset)
		: Event(EventCategory::Input, EventType::MouseScrollY), mOffset(offset)
	{}
	double MouseScrollYEvent::GetOffset() const { return mOffset; }

	/************************* MOUSE MOVE EVENT CLASS *********************************/
	MouseMoveEvent::MouseMoveEvent(double xPos, double yPos)
		: Event(EventCategory::Input, EventType::MouseMove), mXPos(xPos), mYPos(yPos)
	{}
	double MouseMoveEvent::GetXPos() const { return mXPos; }
	double MouseMoveEvent::GetYPos() const { return mYPos; }
}
