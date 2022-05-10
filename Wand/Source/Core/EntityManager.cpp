#include "WandPCH.h"
#include "EntityManager.h"
#include "Graphics/FontManager.h"

namespace wand
{
	EntityManager::EntityManager()
		: mEntities(), mFontManager(nullptr)
	{}

	void EntityManager::Init(FontManager* fontManager) { mFontManager = fontManager; }

	Rectangle* EntityManager::AddRectangle(Color color)
	{
		mEntities.emplace_back(std::unique_ptr<Rectangle>(new Rectangle(color)));
		return static_cast<Rectangle*>(mEntities.back().get());
	}

	Sprite* EntityManager::AddSprite(const std::string& imagePath)
	{
		mEntities.emplace_back(std::unique_ptr<Sprite>(new Sprite(imagePath)));
		return static_cast<Sprite*>(mEntities.back().get());
	}

	TextBox* EntityManager::AddTextBox(const std::string& fontName, unsigned int fontSize, Color color)
	{
		// Create and setup a text UI entity
		TextBox* text = new TextBox(fontName, fontSize, color);
		SetFontManager(static_cast<TextGFX*>(text->GetDrawable()));

		mEntities.emplace_back(std::unique_ptr<TextBox>(text));
		return static_cast<TextBox*>(mEntities.back().get());
	}

	Button* EntityManager::AddButton(std::string imagePath, std::string fontName, unsigned int fontSize, Color textColor)
	{
		// Create and setup a button UI entity
		Button* button = new Button(imagePath, fontName, fontSize, textColor);
		SetFontManager(static_cast<TextGFX*>(button->GetTextDrawable()));

		mEntities.emplace_back(std::unique_ptr<Button>(button));
		return static_cast<Button*>(mEntities.back().get());
	}

	Button* EntityManager::AddButton(Color bgColor, std::string fontName, unsigned int fontSize, Color textColor)
	{
		// Create and setup a button UI entity
		Button* button = new Button(bgColor, fontName, fontSize, textColor);
		SetFontManager(static_cast<TextGFX*>(button->GetTextDrawable()));

		mEntities.emplace_back(std::unique_ptr<Button>(button));
		return static_cast<Button*>(mEntities.back().get());
	}

	std::vector<std::unique_ptr<UIEntity>>& EntityManager::GetEntities() { return mEntities; }

	void EntityManager::SetFontManager(TextGFX* textGFX) const
	{
		textGFX->SetFontManager(mFontManager);
	}
}
