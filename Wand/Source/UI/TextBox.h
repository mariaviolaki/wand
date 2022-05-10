#pragma once

#include "Graphics/TextGFX.h"
#include "UIEntity.h"

namespace wand
{
	class TextBox : public UIEntity
	{
	public:
		TextBox(const std::string& fontName, unsigned int fontSize, Color color);
		Drawable* GetDrawable() const override;
		Transform* GetTransform() const override;
		// Set the new text by overwriting the existing one
		void SetText(const std::string& newText);
		// Set the text to be centered or to start from the top left corner
		void SetCenteredText(bool isTextCentered);

	private:
		std::shared_ptr<TextGFX> mDrawable;
	};
}
