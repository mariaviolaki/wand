#pragma once

#include "Graphics/SpriteGFX.h"
#include "UIComponent.h"

namespace wand
{
	class Sprite : public SpriteGFX, public UIComponent
	{
	public:
		Sprite(const std::string& imagePath);

		void OnClick(const std::function<void()>& fun) override;
	};
}
