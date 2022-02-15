#pragma once

#include "msdfgen/msdfgen/msdfgen.h"
#include "msdfgen/msdfgen/msdfgen-ext.h"
#include "msdfgen/msdf-atlas-gen/msdf-atlas-gen.h"

namespace wand
{
    class Font
    {
    public:
        Font(const std::string& name, const std::string& path, unsigned int size = MSDF_ATLAS_DEFAULT_EM_SIZE);
        ~Font();

        const std::string GetName() const;
        const std::string GetPath() const;
        const unsigned int GetSize() const;

        const msdf_atlas::BitmapAtlasStorage<unsigned char, 3>& GetAtlas() const;
        const std::vector<msdf_atlas::GlyphGeometry>& GetGlyphs() const;

    private:
        std::string mName;
        std::string mPath;
        unsigned int mSize;
        msdfgen::FreetypeHandle* mFreetypeHandle;
        msdfgen::FontHandle* mFontHandle;
        // Atlas texture data
        msdf_atlas::BitmapAtlasStorage<unsigned char, 3> mAtlasData;
        // Glyphs and their coordinates in the atlas
        std::vector<msdf_atlas::GlyphGeometry> mGlyphs;

        bool InitFontHandles(const std::string fontPath);
        void ReleaseFontHandles();
        void CreateAtlas();
    };
}
