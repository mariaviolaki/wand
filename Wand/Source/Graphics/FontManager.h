#pragma once

#include "Base/Font.h"

namespace wand
{
	class FontManager
	{
	public:
		FontManager();

		// Save a new font
		void Add(std::string filepath, std::string name);
		// Use an existing font
		Font* Get(const std::string& fontName, unsigned int fontSize);

	private:
		std::vector<std::unique_ptr<Font>> mFonts;
	};
}
