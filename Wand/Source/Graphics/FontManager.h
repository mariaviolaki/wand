#pragma once

#include "Base/Font.h"

namespace wand
{
	class FontManager
	{
	public:
		static void Add(Font* font);
		static Font* Get(const std::string& fontName, unsigned int fontSize);
		static void Clear();

	private:
		static std::vector<Font*> sFonts;

		FontManager() {};
	};
}
