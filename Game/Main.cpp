#include "Wand.h"

#include "msdfgen/msdfgen/msdfgen.h"
#include "msdfgen/msdfgen/msdfgen-ext.h"
#include "msdfgen/msdf-atlas-gen/msdf-atlas-gen.h"

using namespace msdfgen;
using namespace msdf_atlas;

int main()
{
	// MSDFGEN
	FreetypeHandle* ft = initializeFreetype();
	if (ft)
	{
		FontHandle* font = loadFont(ft, "C:\\Windows\\Fonts\\arialbd.ttf");
		if (font)
		{
			Shape shape;
			if (loadGlyph(shape, font, 'A'))
			{
				shape.normalize();
				//                      max. angle
				edgeColoringSimple(shape, 3.0);
				//           image width, height
				Bitmap<float, 3> msdf(32, 32);
				//                     range, scale, translation
				generateMSDF(msdf, shape, 4.0, 1.0, Vector2(4.0, 4.0));
				savePng(msdf, "output.png");
			}
			destroyFont(font);
		}
		deinitializeFreetype(ft);
	}

	// MSDF-ATLAS-GEN
	//bool success = false;
	// Initialize instance of FreeType library
	if (msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype())
	{
		// Load font file
		if (msdfgen::FontHandle* font = msdfgen::loadFont(ft, "C:\\Windows\\Fonts\\arialbd.ttf"))
		{
			// Storage for glyph geometry and their coordinates in the atlas
			std::vector<GlyphGeometry> glyphs;
			// FontGeometry is a helper class that loads a set of glyphs from a single font.
			// It can also be used to get additional font metrics, kerning information, etc.
			FontGeometry fontGeometry(&glyphs);
			// Load a set of character glyphs:
			// The second argument can be ignored unless you mix different font sizes in one atlas.
			// In the last argument, you can specify a charset other than ASCII.
			// To load specific glyph indices, use loadGlyphs instead.
			fontGeometry.loadCharset(font, 1.0, Charset::ASCII);
			// Apply MSDF edge coloring. See edge-coloring.h for other coloring strategies.
			const double maxCornerAngle = 3.0;
			for (GlyphGeometry& glyph : glyphs)
				glyph.edgeColoring(&msdfgen::edgeColoringInkTrap, maxCornerAngle, 0);
			// TightAtlasPacker class computes the layout of the atlas.
			TightAtlasPacker packer;
			// Set atlas parameters:
			// setDimensions or setDimensionsConstraint to find the best value
			packer.setDimensionsConstraint(TightAtlasPacker::DimensionsConstraint::SQUARE);
			// setScale for a fixed size or setMinimumScale to use the largest that fits
			packer.setMinimumScale(24.0);
			// setPixelRange or setUnitRange
			packer.setPixelRange(2.0);
			packer.setMiterLimit(1.0);
			// Compute atlas layout - pack glyphs
			packer.pack(glyphs.data(), glyphs.size());
			// Get final atlas dimensions
			int width = 0, height = 0;
			packer.getDimensions(width, height);
			// The ImmediateAtlasGenerator class facilitates the generation of the atlas bitmap.
			ImmediateAtlasGenerator<
				float, // pixel type of buffer for individual glyphs depends on generator function
				3, // number of atlas color channels
				(GeneratorFunction<float, 3>) &msdfGenerator, // function to generate bitmaps for individual glyphs
				BitmapAtlasStorage<byte, 3> // class that stores the atlas bitmap
				// For example, a custom atlas storage class that stores it in VRAM can be used.
			> generator(width, height);
			// GeneratorAttributes can be modified to change the generator's default settings.
			GeneratorAttributes attributes;
			generator.setAttributes(attributes);
			generator.setThreadCount(4);
			// Generate atlas bitmap
			generator.generate(glyphs.data(), glyphs.size());
			// The atlas bitmap can now be retrieved via atlasStorage as a BitmapConstRef.
			// The glyphs array (or fontGeometry) contains positioning data for typesetting text.
			//success = myProject::submitAtlasBitmapAndLayout(generator.atlasStorage(), glyphs);
			// Cleanup
			msdfgen::destroyFont(font);
		}
		msdfgen::deinitializeFreetype(ft);
	}


	wand::App app;

	glm::vec4 color = { 1.0f, 0.0f, 1.0f, 1.0f };
	float rectSize = 10.0f;
	float spriteSize = 100.0f;

	while (app.IsRunning())
	{
		//std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

		std::vector<std::shared_ptr<wand::Rectangle>> rects;
		// Render solid-color rectangles
		for (float x = 0.0f; x <= app.GetWidth(); x += rectSize + 10.0f)
		{
			for (float y = 0.0f; y <= app.GetHeight(); y += rectSize + 10.0f)
			{
				std::shared_ptr<wand::Rectangle> r = std::make_shared<wand::Rectangle>(color);
				r->SetPosition(x, y);
				rects.emplace_back(r);
				wand::Renderer::Draw(r.get());
			}
		}

		std::vector<std::shared_ptr<wand::Sprite>> sprites;
		// Render transparent and non-transparent sprites
		for (int x = 0; x < app.GetWidth(); x += spriteSize + 50.0f)
		{
			for (int y = 0; y < app.GetHeight(); y += spriteSize + 50.0f)
			{
				float rem = y % 20;
				std::string path = "Images\\wand." + std::string((rem == 0) ? "jpg" : "png");
				std::shared_ptr<wand::Sprite> s = std::make_shared<wand::Sprite>(path);
				s->SetPosition(x, y);
				s->SetWidth(spriteSize);
				s->SetHeight(spriteSize);
				sprites.emplace_back(s);
				wand::Renderer::Draw(s.get());
			}
		}

		app.Update();

		//std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();
		//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms\n";
	}

	return 0;
}
