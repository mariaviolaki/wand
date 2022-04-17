#pragma once

#include "Graphics/TextGFX.h"
#include "UIEntity.h"

namespace wand
{
	class TextBox : public UIEntity
	{
	public:
		TextBox(const std::string& fontName, unsigned int fontSize, const glm::vec4& color);
		Drawable* GetDrawable() const override;
		void SetText(const std::string& newText);

	private:
		std::shared_ptr<TextGFX> drawable;
	};
}
