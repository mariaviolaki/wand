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
		Rectangle& AddRectangle(glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f });
		Sprite& AddSprite(const std::string& imagePath);
		TextBox& AddTextBox(const std::string& fontName, unsigned int fontSize, const glm::vec4& color);
		Button& AddButton(std::string imagePath, std::string fontName, unsigned int fontSize, glm::vec4 textColor);
		Button& AddButton(glm::vec4 bgColor, std::string fontName, unsigned int fontSize, glm::vec4 textColor);
		std::vector<std::unique_ptr<UIEntity>>& GetEntities();

	private:
		std::vector<std::unique_ptr<UIEntity>> mEntities;
		FontManager* mFontManager;

		// Set the font manager needed for the text's initialization
		void SetFontManager(TextGFX* textGFX) const;
	};
}
