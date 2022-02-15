#pragma once

#include "msdfgen/msdfgen/msdfgen.h"
#include "msdfgen/msdf-atlas-gen/msdf-atlas-gen.h"

namespace wand
{
	enum class ColorFormat
	{
		RGB = 3, RGBA
	};

	class Texture
	{
	public:
		Texture();
		Texture(const std::string& imagePath);
		Texture(const msdf_atlas::BitmapAtlasStorage<unsigned char, 3>& fontAtlas);
		~Texture();

		unsigned int GetId() const;
		unsigned int GetTexSlot() const;
		int GetWidth() const;
		int GetHeight() const;
		void SetColorFormat(ColorFormat format);

		void Bind(unsigned int slot);
		void Unbind() const;

	private:
		unsigned int mId;
		std::string mImagePath;
		unsigned int mTexSlot;
		int mWidth;
		int mHeight;
		int mBytesPerPixel;
		ColorFormat mColorFormat;
		unsigned char* mImageData;

		void ConfigTexture(unsigned int minFilter) const;
		void LoadWhiteTexture();
		void LoadSpriteTexture();
		void LoadFontTexture(const msdf_atlas::BitmapAtlasStorage<unsigned char, 3>& fontAtlas);
		void FindColorFormat();
	};
}
