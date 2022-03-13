#pragma once

#include "Graphics/TextGFX.h"
#include "UIComponent.h"

namespace wand
{
	class Text : public TextGFX, public UIComponent
	{
	public:
		Text(const std::string& fontName, unsigned int fontSize, const glm::vec4& color);
	};
}
