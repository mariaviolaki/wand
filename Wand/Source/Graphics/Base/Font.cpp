#include "WandPCH.h"
#include "Font.h"

namespace wand
{
	Font::Font(const std::string& name, const std::string& path, unsigned int size)
		: mName(name), mPath(path), mSize(size), mFreetype(nullptr), mFace(nullptr),
		mAtlasWidth(0), mAtlasHeight(0)
	{
		InitFreeType();
		LoadFontData();
	}

	Font::~Font()
	{
		// Repeat for each glyph in the font
		for (int c = 32; c < 128; c++)
			delete mCharacters.at(c);	// delete glyph data

		ClearFreeType();
	}

	const std::string Font::GetName() const { return mName; }
	const std::string Font::GetPath() const { return mPath; }
	const unsigned int Font::GetSize() const { return mSize; }

	unsigned int Font::GetAtlasWidth() const { return mAtlasWidth; }
	unsigned int Font::GetAtlasHeight() const { return mAtlasHeight; }
	const FT_Face& Font::GetFontFace() const { return mFace; }
	const std::unordered_map<char, Glyph*>& Font::GetGlyphs() const	{ return mCharacters; }

	// Initialize FreeType resources
	void Font::InitFreeType()
	{
		// Initialize FreeType library
		if (FT_Init_FreeType(&mFreetype))
			std::cout << "FreeType: Failed to initialize FreeType library.\n";
		// Load the given font
		if (FT_New_Face(mFreetype, mPath.c_str(), 0, &mFace))
			std::cout << "FreeType: Failed to load font.\n";
		FT_Set_Pixel_Sizes(mFace, 0, mSize);
	}

	// Load the glyph data from the font and create an atlas
	void Font::LoadFontData()
	{
		FT_GlyphSlot glyphSlot = mFace->glyph;
		float xPos = 0.0f;
		for (int c = 32; c < 128; c++)
		{
			// Load a specific ASCII character from the font
			if (FT_Load_Char(mFace, c, FT_LOAD_RENDER))
			{
				std::cout << "FreeType: Failed to load character " << c << std::endl;
				continue;
			}

			// Create a new glyph and add it to the unordered map
			CreateGlyph(xPos, c, glyphSlot);
			// Move the x position for the next glyph in the atlas
			xPos += glyphSlot->bitmap.width;

			// Add the glyph's width to the atlas width
			mAtlasWidth += glyphSlot->bitmap.width;
			// Store the height of the tallest glyph
			mAtlasHeight = std::max((int)mAtlasHeight, (int)glyphSlot->bitmap.rows);
		}
	}

	// Create a new glyph and add it to the unordered map
	void Font::CreateGlyph(const float xPos, const int character, const FT_GlyphSlot& glyphSlot)
	{
		// Allocate memory for the glyph
		Glyph* glyph = new Glyph;
		glyph->width = glyphSlot->bitmap.width;
		glyph->height = glyphSlot->bitmap.rows;
		glyph->bearingX = glyphSlot->bitmap_left;
		glyph->bearingY = glyphSlot->bitmap_top;
		glyph->advanceX = glyphSlot->advance.x / 64;
		glyph->atlasCoordX = xPos;
		mCharacters.insert(std::pair<char, Glyph*>(character, glyph));
	}

	// Clear FreeType resources
	void Font::ClearFreeType()
	{
		FT_Done_Face(mFace);
		FT_Done_FreeType(mFreetype);
	}
}
