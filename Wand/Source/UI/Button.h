#pragma once

#include "TextBox.h"
#include "Rectangle.h"
#include "Sprite.h"

namespace wand
{
	class Button : public UIEntity
	{
	public:
		Button(std::string imagePath, std::string fontName, unsigned int fontSize, Color textColor);
		Button(Color bgColor, std::string fontName, unsigned int fontSize, Color textColor);

		// Get the drawable of the background entity (rectangle or sprite)
		Drawable* GetDrawable() const override;
		Drawable* GetTextDrawable() const;
		Transform* GetTransform() const override;
		Transform* GetTextTransform() const;
		void SetText(std::string text);
		// Change the visibility/availability of the button and its components
		void Show() override;
		void Hide() override;
		void Enable() override;
		void Disable() override;

	private:
		std::unique_ptr<TextBox> mTextBox;
		std::unique_ptr<Rectangle> mRectangle;
		std::unique_ptr<Sprite> mSprite;

		void CenterText();
	};
}