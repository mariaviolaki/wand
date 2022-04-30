#pragma once

#include "Graphics/SpriteGFX.h"
#include "UIEntity.h"

namespace wand
{
	class Sprite : public UIEntity
	{
	public:
		Sprite(const std::string& imagePath);
		Drawable* GetDrawable() const override;
		Transform* GetTransform() const override;

	private:
		std::shared_ptr<SpriteGFX> drawable;
	};
}
