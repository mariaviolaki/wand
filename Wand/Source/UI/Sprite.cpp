#include "WandPCH.h"
#include "Sprite.h"

namespace wand
{
	Sprite::Sprite(const std::string& imagePath)
		: SpriteGFX(imagePath), UIComponent(GetGFXTransform(), false)
	{}
}
