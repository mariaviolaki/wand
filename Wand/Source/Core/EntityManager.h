#pragma once

#include "UI/UIEntity.h"
#include "UI/Rectangle.h"
#include "UI/Sprite.h"
#include "UI/TextBox.h"
#include "UI/Button.h"

namespace wand
{
	class EntityManager
	{
	public:
		EntityManager();

		void Init(FontManager* fontManager);
		// Create and render a new rectangle
		Rectangle* AddRectangle(Color color = Color(255, 255, 255, 0));
		// Create and render a new sprite
		Sprite* AddSprite(const std::string& imagePath);
		// Create and render a new textbox
		TextBox* AddTextBox(const std::string& fontName, unsigned int fontSize, Color color);
		// Create and render a new image button
		Button* AddButton(std::string imagePath, std::string fontName, unsigned int fontSize, Color textColor);
		// Create and render a new rectangle button
		Button* AddButton(Color bgColor, std::string fontName, unsigned int fontSize, Color textColor);
		// Get all the UI entities that have been created
		std::vector<std::unique_ptr<UIEntity>>& GetEntities();

	private:
		std::vector<std::unique_ptr<UIEntity>> mEntities;
		FontManager* mFontManager;

		// Set the font manager needed for the text's initialization
		void SetFontManager(TextGFX* textGFX) const;
	};
}
