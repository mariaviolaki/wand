#pragma once

#include "Graphics/TextGFX.h"
#include "UIComponent.h"

namespace wand
{
	class Text : public UIComponent
	{
	public:
		Text(const std::string& fontName, unsigned int fontSize, const glm::vec4& color);
		Drawable* GetDrawable() const override;
		void Add(const std::string& newText);

	private:
		std::shared_ptr<TextGFX> drawable;
	};
}
