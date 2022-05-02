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
		Rectangle& AddRectangle(Color color = Color(255, 255, 255, 0));
		Sprite& AddSprite(const std::string& imagePath);
		TextBox& AddTextBox(const std::string& fontName, unsigned int fontSize, Color color);
		Button& AddButton(std::string imagePath, std::string fontName, unsigned int fontSize, Color textColor);
		Button& AddButton(Color bgColor, std::string fontName, unsigned int fontSize, Color textColor);
		std::vector<std::unique_ptr<UIEntity>>& GetEntities();

	private:
		std::vector<std::unique_ptr<UIEntity>> mEntities;
		FontManager* mFontManager;

		// Set the font manager needed for the text's initialization
		void SetFontManager(TextGFX* textGFX) const;
	};
}
