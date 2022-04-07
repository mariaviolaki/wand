#include "WandPCH.h"
#include "EntityManager.h"
#include "Graphics/FontManager.h"

namespace wand
{
	EntityManager::EntityManager()
		: mEntities(), mFontManager(nullptr)
	{}

	void EntityManager::Init(FontManager* fontManager)
	{
		mFontManager = fontManager;
	}

	Rectangle& EntityManager::AddRectangle(glm::vec4 color)
	{
		mEntities.emplace_back(std::unique_ptr<Rectangle>(new Rectangle(color)));
		return static_cast<Rectangle&>(*mEntities.back().get());
	}

	Sprite& EntityManager::AddSprite(const std::string& imagePath)
	{
		mEntities.emplace_back(std::unique_ptr<Sprite>(new Sprite(imagePath)));
		return static_cast<Sprite&>(*mEntities.back().get());
	}

	Text& EntityManager::AddText(const std::string& fontName, unsigned int fontSize, const glm::vec4& color)
	{
		// Create a text UI entity
		Text* text = new Text(fontName, fontSize, color);
		// Set the font manager needed for the text's initialization
		TextGFX* drawable = static_cast<TextGFX*>(text->GetDrawable());
		drawable->SetFontManager(mFontManager);

		mEntities.emplace_back(std::unique_ptr<Text>(text));
		return static_cast<Text&>(*mEntities.back().get());
	}

	std::vector<std::unique_ptr<UIEntity>>& EntityManager::GetEntities() { return mEntities; }
}
