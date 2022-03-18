#pragma once

#include "Graphics/SpriteGFX.h"
#include "UIComponent.h"

namespace wand
{
	class Sprite : public UIComponent
	{
	public:
		Sprite(const std::string& imagePath);
		Drawable* GetDrawable() const override;

	private:
		std::shared_ptr<SpriteGFX> drawable;
	};
}
