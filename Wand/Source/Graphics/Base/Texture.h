#pragma once

#include "Font.h"

namespace wand
{
	enum class ColorFormat
	{
		RED = 1, RGB = 3, RGBA
	};

	class Texture
	{
	public:
		Texture();
		Texture(const std::string& imagePath);
		Texture(const Font& font);
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

		void ConfigTexture() const;
		void LoadWhiteTexture();
		void LoadSpriteTexture();
		void LoadFontTexture(const Font& font);
		void FindColorFormat();
	};
}
