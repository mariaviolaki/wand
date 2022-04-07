#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H

namespace wand
{
    struct Glyph
    {
        float width;        // width in pixels
        float height;       // height in pixels
        float bearingX;     // distance from origin to left side
        float bearingY;     // distance from origin to top side
        float advanceX;     // distance from origin to next glyph's origin
        float atlasCoordX;  // x coordinate in the atlas
    };

    class Font
    {
    public:
        Font(const std::string& path, const std::string& name, unsigned int size = 24);
        ~Font();

        const std::string GetName() const;
        const std::string GetPath() const;
        const unsigned int GetSize() const;

        unsigned int GetAtlasWidth() const;
        unsigned int GetAtlasHeight() const;
        const FT_Face& GetFontFace() const;
        const std::unordered_map<char, Glyph*>& GetGlyphs() const;

    private:
        std::string mPath;
        std::string mName;
        unsigned int mSize;
        FT_Library mFreetype;
        FT_Face mFace;
        std::unordered_map<char, Glyph*> mCharacters;
        unsigned int mAtlasWidth;
        unsigned int mAtlasHeight;

        void InitFreeType();
        void LoadFontData();
        void CreateGlyph(const float xPos, const int character, const FT_GlyphSlot& glyphSlot);
        void ClearFreeType();
    };
}
