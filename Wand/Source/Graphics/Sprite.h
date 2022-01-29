#pragma once

#include "Drawable.h"

namespace wand
{
	class Sprite : public Drawable
	{
	public:
		Sprite(const std::string& imagePath);

		void SetTextureSlot(int slot) override;

	private:
		// The color will always be { 1, 1, 1, 1 }
		void SetColor(glm::vec4 color) override {};
	};
}
