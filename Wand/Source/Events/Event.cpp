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

	/************************* WINDOW RESIZE EVENT CLASS ******************************/
	WindowResizeEvent::WindowResizeEvent(unsigned int width, unsigned int height)
		: Event(EventCategory::Window, EventType::WindowResize), mWidth(width), mHeight(height)
	{}
	unsigned int WindowResizeEvent::GetWidth() const { return mWidth; }
	unsigned int WindowResizeEvent::GetHeight() const { return mHeight; }

	/************************* KEY PRESS EVENT CLASS **********************************/
	KeyPressEvent::KeyPressEvent(int key, bool isCapital)
		: Event(EventCategory::Input, EventType::KeyPress), mKey(key), mIsCapital(isCapital)
	{}
	int KeyPressEvent::GetKey() const { return mKey; }
	bool KeyPressEvent::IsCapital() const { return mIsCapital; }

	/************************* KEY RELEASE EVENT CLASS ********************************/
	KeyReleaseEvent::KeyReleaseEvent(int key, bool isCapital)
		: Event(EventCategory::Input, EventType::KeyRelease), mKey(key), mIsCapital(isCapital)
	{}
	int KeyReleaseEvent::GetKey() const { return mKey; }
	bool KeyReleaseEvent::IsCapital() const { return mIsCapital; }

	/************************* MOUSE BUTTON PRESS EVENT CLASS *************************/
	MouseButtonPressEvent::MouseButtonPressEvent(int button)
		: Event(EventCategory::Input, EventType::MouseButtonPress), mButton(button)
	{}
	int MouseButtonPressEvent::GetButton() const { return mButton; }

	/************************* MOUSE BUTTON RELEASE EVENT CLASS ***********************/
	MouseButtonReleaseEvent::MouseButtonReleaseEvent(int button)
		: Event(EventCategory::Input, EventType::MouseButtonRelease), mButton(button)
	{}
	int MouseButtonReleaseEvent::GetButton() const { return mButton; }

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
