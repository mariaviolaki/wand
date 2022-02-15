#include "WandPCH.h"
#include "Font.h"

namespace wand
{
	/***************************Constructors/Destructor***********************************/
	Font::Font(const std::string& name, const std::string& path, unsigned int size)
		: mName(name), mPath(path), mSize(size), mFreetypeHandle(nullptr), mFontHandle(nullptr)
	{
		if (!InitFontHandles(path))
			std::cout << "FontAtlas: Unable to load font file.\n";
		CreateAtlas();
	}
	
	Font::~Font()
	{
		ReleaseFontHandles();
	}

	const std::string Font::GetName() const { return mName;	}

	const std::string Font::GetPath() const { return mPath; }

	const unsigned int Font::GetSize() const { return mSize; }

	/******************************Font Operations************************************/
	const msdf_atlas::BitmapAtlasStorage<msdfgen::byte, 3>& Font::GetAtlas() const
	{
		return mAtlasData;
	}

	const std::vector<msdf_atlas::GlyphGeometry>& Font::GetGlyphs() const
	{
		return mGlyphs;
	}

	bool Font::InitFontHandles(const std::string fontPath)
	{
		// Initialize the freetype handle and load a font from a given path
		if (mFreetypeHandle = msdfgen::initializeFreetype())
			mFontHandle = msdfgen::loadFont(mFreetypeHandle, fontPath.c_str());
		return mFontHandle;
	}

	void Font::ReleaseFontHandles()
	{
		// Release font resources
		if (mFontHandle) msdfgen::destroyFont(mFontHandle);
		if (mFreetypeHandle) msdfgen::deinitializeFreetype(mFreetypeHandle);
	}

	// Create a font atlas bitmap using multi-channel distance fields
	void Font::CreateAtlas()
	{
		// Storage for glyph geometry and their coordinates in the atlas
		std::vector<msdf_atlas::GlyphGeometry> glyphs;
		// Helper class that loads a set of glyphs from a font and gets font metrics
		msdf_atlas::FontGeometry fontGeometry(&glyphs);
		// Load a set of character glyphs
		fontGeometry.loadCharset(mFontHandle, 1.0, msdf_atlas::Charset::ASCII);
		// Apply MSDF edge coloring
		const double maxCornerAngle = 3.0;
		for (msdf_atlas::GlyphGeometry& glyph : glyphs)
			glyph.edgeColoring(&msdfgen::edgeColoringInkTrap, maxCornerAngle, 0);
		// Compute the layout of the atlas
		msdf_atlas::TightAtlasPacker packer;
		// Find the best value
		packer.setDimensionsConstraint(msdf_atlas::TightAtlasPacker::DimensionsConstraint::POWER_OF_TWO_RECTANGLE);
		// Set font size
		packer.setMinimumScale(mSize);
		//packer.setPadding(0);
		packer.setPixelRange(2.0);
		packer.setMiterLimit(1.0);
		// Compute atlas layout - pack glyphs
		packer.pack(glyphs.data(), glyphs.size());
		// Get final atlas dimensions
		int width = 0, height = 0;
		packer.getDimensions(width, height);
		// Create a generator for the atlas bitmap
		msdf_atlas::ImmediateAtlasGenerator<float, 3,
			(msdf_atlas::GeneratorFunction<float, 3>) &msdf_atlas::msdfGenerator,
			msdf_atlas::BitmapAtlasStorage<unsigned char, 3>
		> generator(width, height);
		// Set the generator's attributes
		msdf_atlas::GeneratorAttributes attributes;
		generator.setAttributes(attributes);
		generator.setThreadCount(4);
		// Generate atlas bitmap
		generator.generate(glyphs.data(), glyphs.size());
		// Save the atlas bitmap in the atlasStorage
		mAtlasData = generator.atlasStorage();
		// Save positioning data for typesetting text in the glyphs array
		mGlyphs = glyphs;
	}
}
