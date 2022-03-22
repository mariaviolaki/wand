#include "WandPCH.h"
#include "FontManager.h"

namespace wand
{
	std::vector<Font*> FontManager::sFonts;

	void FontManager::Add(Font* font)
	{
		sFonts.emplace_back(font);
	}

	Font* FontManager::Get(const std::string& fontName, unsigned int fontSize)
	{
		std::string savedName = "";
		std::string savedPath = "";
		for (int i = 0; i < sFonts.size(); i++)
		{
			if (sFonts[i]->GetName() == fontName)
			{
				// If there is a font with this name and size, return it
				if (sFonts[i]->GetSize() == fontSize)
					return sFonts[i];
				// Save the name and path if the two fonts have the same name
				savedName = fontName;
				savedPath = sFonts[i]->GetPath();
			}
		}

		if (savedName != "" && savedPath != "")
		{
			// Create and return a new font with an existing name but with a different size
			Font* newFont = new Font(savedName, savedPath, fontSize);
			sFonts.emplace_back(newFont);
			return newFont;
		}

		std::cout << "Font '" << fontName << "' not found.\n";
		return nullptr;
	}

	void FontManager::Clear()
	{
		// Delete all fonts saved on the heap
		for (int i = 0; i < sFonts.size(); i++)
			delete sFonts[i];
	}
}
