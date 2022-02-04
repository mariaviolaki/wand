#include "WandPCH.h"
#include "Texture.h"

#include "glad/glad.h"
#include "stb/stb_image.h"
#include "Utils.h"

namespace wand
{
	/********************** CONSTRUCTORS *************************/

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

	Texture::Texture(const std::string& imagePath)
		: mImagePath(imagePath), mTexSlot(1), mColorFormat(ColorFormat::RGBA)
	{
		// Allocate space and bind a 2D texture
		glGenTextures(1, &mId);
		Bind(mTexSlot);

		ConfigTexture();
		//FindColorFormat(); // not reliable
		LoadTexture();
	}

	Texture::~Texture()
	{
		if (mImageData)
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

	void Texture::LoadWhiteTexture()
	{
		unsigned char whiteTexture[] = {255, 255, 255, 255};
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, whiteTexture);
	}

	void Texture::LoadTexture()
	{
		int openglFormat = (mColorFormat == ColorFormat::RGB) ? GL_RGB : GL_RGBA;

		// Flip the image vertically so that it's compatible with OpenGL
		stbi_set_flip_vertically_on_load(1);
		// Load the image and fill in its parameters
		mImageData = stbi_load(mImagePath.c_str(), &mWidth, &mHeight, &mBytesPerPixel, (int)mColorFormat);

		glTexImage2D(GL_TEXTURE_2D,
			0, openglFormat, mWidth, mHeight, 0, openglFormat, GL_UNSIGNED_BYTE, mImageData);
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
