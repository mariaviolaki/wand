#include "WandPCH.h"
#include "Rectangle.h"
#include "Input/Input.h"

namespace wand
{
	Rectangle::Rectangle(glm::vec4 color)
		: RectangleGFX(color)
	{}

	void Rectangle::OnClick(const std::function<void()>&fun)
	{
		glm::vec3 pos = GetPosition();
		if (Input::IsMouseInArea(pos.x, pos.y, GetWidth(), GetHeight())
			&& Input::GetMouseButtonStatus(MOUSE_BUTTON_LEFT) == ButtonStatus::PRESSED)
		{
			fun();
		}
	}
}
