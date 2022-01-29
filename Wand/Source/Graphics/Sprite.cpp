#include "WandPCH.h"
#include "Sprite.h"

namespace wand
{
	Sprite::Sprite(const std::string& imagePath)
		: Drawable(imagePath)
	{}

	void Sprite::SetTextureSlot(int slot) { Drawable::SetTextureSlot(slot); }
}
