#include "WandPCH.h"
#include "Sprite.h"

namespace wand
{
	Sprite::Sprite(const std::string& imagePath)
		: Drawable(std::filesystem::current_path().string() + "\\" + imagePath)
	{}

	void Sprite::SetTextureSlot(int slot) { Drawable::SetTextureSlot(slot); }
}
