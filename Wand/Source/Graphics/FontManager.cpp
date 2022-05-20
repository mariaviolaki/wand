#include "WandPCH.h"
#include "FontManager.h"
#include "Utils/Logger.h"

namespace wand
{
	FontManager::FontManager()
		: mFonts()
	{}

	void FontManager::Add(std::string filepath, std::string name)
	{
		// If the file exists, add a default-sized font to the list
		if (std::filesystem::exists(filepath))
			mFonts.emplace_back(std::unique_ptr<Font>(new Font(filepath, name, 20)));
		else
			Logger::EngineLog("FontManager", "Font not found in location: " + filepath + "\n");
	}

	Font* FontManager::Get(const std::string& fontName, unsigned int fontSize)
	{
		std::string savedName = "";
		std::string savedPath = "";
		for (int i = 0; i < mFonts.size(); i++)
		{
			if (mFonts[i]->GetName() == fontName)
			{
				// If there is a font with this name and size, return it
				if (mFonts[i]->GetSize() == fontSize)
					return mFonts[i].get();
				// Save the name and path if the two fonts have the same name
				savedName = fontName;
				savedPath = mFonts[i]->GetPath();
			}
		}

		if (savedName != "" && savedPath != "")
		{
			// Create and return a new font with an existing name but with a different size
			Font* newFont = new Font(savedPath, savedName, fontSize);
			mFonts.emplace_back(std::unique_ptr<Font>(newFont));
			return newFont;
		}

		Logger::EngineLog("FontManager", "Font '" + fontName + "' not found.\n");
		return nullptr;
	}
}
