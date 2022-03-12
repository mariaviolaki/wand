#include "WandPCH.h"
#include "Sprite.h"
#include "Input/Input.h"

namespace wand
{
	Sprite::Sprite(const std::string& imagePath)
		: SpriteGFX(imagePath)
	{}

	void Sprite::OnClick(const std::function<void()>&fun)
	{
		glm::vec3 pos = GetPosition();
		if (Input::IsMouseInArea(pos.x, pos.y, GetWidth(), GetHeight())
			&& Input::GetMouseButtonStatus(MOUSE_BUTTON_LEFT) == ButtonStatus::PRESSED)
		{
			fun();
		}
	}
}
