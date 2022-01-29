#pragma once

#include "Drawable.h"
#include "Graphics.h"
#include "OpenGL/Texture.h"

namespace wand
{
	class Rectangle : public Drawable
	{
	public:
		Rectangle(glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f });

		void SetColor(glm::vec4 color) override;

	private:
		// The texture slot will always be 0
		void SetTextureSlot(int slot) override {};
	};
}
