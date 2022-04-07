#pragma once

#include "Base/Font.h"

namespace wand
{
	class FontManager
	{
	public:
		FontManager();

		void Add(std::string filepath, std::string name, unsigned int size);
		Font* Get(const std::string& fontName, unsigned int fontSize);

	private:
		std::vector<std::unique_ptr<Font>> mFonts;
	};
}
