#pragma once

#include "UI/UIEntity.h"
#include "UI/Rectangle.h"
#include "UI/Sprite.h"
#include "UI/Text.h"

namespace wand
{
	class EntityManager
	{
	public:
		EntityManager();

		void Init(FontManager* fontManager);
		Rectangle& AddRectangle(glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f });
		Sprite& AddSprite(const std::string& imagePath);
		Text& AddText(const std::string& fontName, unsigned int fontSize, const glm::vec4& color);
		std::vector<std::unique_ptr<UIEntity>>& GetEntities();

	private:
		std::vector<std::unique_ptr<UIEntity>> mEntities;
		FontManager* mFontManager;
	};
}
