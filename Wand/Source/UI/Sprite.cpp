#include "WandPCH.h"
#include "Sprite.h"

namespace wand
{
	Sprite::Sprite(const std::string& imagePath)
		: drawable(std::make_shared<SpriteGFX>(imagePath)), UIComponent(false)
	{
		SetTransform(drawable->GetTransform());
	}

	Drawable* Sprite::GetDrawable() const { return drawable.get(); }
}
