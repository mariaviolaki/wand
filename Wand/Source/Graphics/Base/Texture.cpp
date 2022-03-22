#include "WandPCH.h"
#include "Texture.h"

#include "glad/glad.h"
#include "stb/stb_image.h"
#include "Utils/Utils.h"

namespace wand
{
	/********************** CONSTRUCTORS *************************/
	// Constructor for rectangles
	Texture::Texture()
		: mImagePath(""), mImageData(nullptr), mTexSlot(0),
		mWidth(1), mHeight(1), mBytesPerPixel(4), mColorFormat(ColorFormat::RGBA)
	{
		// Allocate space and bind a 2D texture
		glGenTextures(1, &mId);
		Bind(mTexSlot);

		ConfigTexture();
		LoadWhiteTexture();
	}
	// Constructor for images
	Texture::Texture(const std::string& imagePath)
		: mImagePath(imagePath), mImageData(nullptr), mTexSlot(1), 
		mWidth(1), mHeight(1), mBytesPerPixel(4), mColorFormat(ColorFormat::RGBA)
	{
		// Allocate space and bind a 2D texture
		glGenTextures(1, &mId);
		Bind(mTexSlot);

		ConfigTexture();
		//FindColorFormat(); // not reliable
		LoadSpriteGFXTexture();
	}

	// Constructor for fonts
	Texture::Texture(const Font& font)
		: mImagePath(""), mImageData(nullptr), mTexSlot(1),	mWidth(font.GetAtlasWidth()), 
		mHeight(font.GetAtlasHeight()), mBytesPerPixel(1), mColorFormat(ColorFormat::RED)
	{
		// Allocate space and bind a 2D texture
		glGenTextures(1, &mId);
		Bind(mTexSlot);

		ConfigTexture();
		LoadFontTexture(font);
	}

	Texture::~Texture()
	{
		if (mImageData && mImagePath != "")
			stbi_image_free(mImageData);
		glDeleteTextures(1, &mId);
	}

	/******************** ACCESSORS/MUTATORS *********************/

	unsigned int Texture::GetId() const	{ return mId; }

	unsigned int Texture::GetTexSlot() const { return mTexSlot;	}

	int Texture::GetWidth() const {	return mWidth; }

	int Texture::GetHeight() const { return mHeight; }

	void Texture::SetColorFormat(ColorFormat format) { mColorFormat = format; }

	/********************* TEXTURE METHODS **********************/

	void Texture::Bind(unsigned int slot)
	{
		mTexSlot = slot;
		// Assign a slot to the texture and bind it
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, mId);
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::ConfigTexture() const
	{
		// Set how the texture will be processed when it needs to be scaled up or down
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // smaller
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // larger
		// Set how (and if) the texture will be repeated if its coords exceed the [0 1] range
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // x axis
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // y axis
	}

	void Texture::LoadWhiteTexture()
	{
		unsigned char whiteTexture[] = {255, 255, 255, 255};
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, whiteTexture);
	}

	void Texture::LoadSpriteGFXTexture()
	{
		int openglFormat = (mColorFormat == ColorFormat::RGB) ? GL_RGB : GL_RGBA;

		// Flip the image vertically so that it's compatible with OpenGL
		stbi_set_flip_vertically_on_load(1);
		// Load the image and fill in its parameters
		mImageData = stbi_load(mImagePath.c_str(), &mWidth, &mHeight, &mBytesPerPixel, (int)mColorFormat);

		glTexImage2D(GL_TEXTURE_2D,
			0, openglFormat, mWidth, mHeight, 0, openglFormat, GL_UNSIGNED_BYTE, mImageData);
	}

	void Texture::LoadFontTexture(const Font& font)
	{
		// Use 1 color channer per pixel
		int openglFormat = GL_RED;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Reserve memory for the individual glyph bitmaps in the atlas
		glTexImage2D(GL_TEXTURE_2D,
			0, GL_RED, font.GetAtlasWidth(), font.GetAtlasHeight(), 0, GL_RED, GL_UNSIGNED_BYTE, 0);

		int xPos = 0;
		// Add all the glyph bitmaps into the same texture
		FT_GlyphSlot glyph = font.GetFontFace()->glyph;
		for (int c = 32; c < 128; c++)
		{
			if (FT_Load_Char(font.GetFontFace(), c, FT_LOAD_RENDER))
				continue;

			glTexSubImage2D(GL_TEXTURE_2D, 0, xPos, 0, 
				glyph->bitmap.width, glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

			xPos += glyph->bitmap.width;
		}
	}

	// Get the pixel data format according to the image extension
	void Texture::FindColorFormat()
	{
		// Get the image format from the given path
		unsigned int pos = mImagePath.find_last_of('.');
		std::string imageType = mImagePath.substr(pos + 1);

		// Return the appropriate color format according to the extension
		if (Utils::ToLowercase(imageType) == "png")
			mColorFormat = ColorFormat::RGBA;
		else // default format
			mColorFormat = ColorFormat::RGB;
	}
}
