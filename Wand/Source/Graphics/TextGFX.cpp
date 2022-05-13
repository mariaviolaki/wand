#include "WandPCH.h"
#include "TextGFX.h"
#include "Core/Window.h"
#include "Utils/Logger.h"

namespace wand
{
	TextGFX::TextGFX(const std::string& fontName, unsigned int fontSize, Color color)
		: Drawable(), mFontManager(nullptr), mFont(nullptr), mFontName(fontName), mFontSize(fontSize),
		mStartFontSize(fontSize), mColor(color), mText(""), mTexture(nullptr), mVertices(), mTextDimens(0.0f),
		mIsTextCentered(false), mOffset({ 0.0f, 0.0f })
	{}

	void TextGFX::SetFontManager(FontManager* fontManager)
	{
		mFontManager = fontManager;
		SetupFont();
	}

	void TextGFX::Add(const std::string& newText)
	{
		if (mText.size() + newText.size() <= MAX_TEXT_LENGTH)
			mText += newText;
		else
			Logger::EngineLog("TextGFX", "Submitted text exceeds max character limit.\n");
	}

	void TextGFX::Clear() { mText = ""; }
	void TextGFX::SetCenteredText(bool isTextCentered) { mIsTextCentered = isTextCentered; }
	void TextGFX::SetFont(std::string fontName, unsigned int fontSize)
	{
		mFontName = fontName;
		mFontSize = fontSize;
		SetupFont();
	}
	unsigned int TextGFX::GetMaxLength() const { return MAX_TEXT_LENGTH; }

	std::string TextGFX::GetFontName() const { return mFontName; }
	unsigned int TextGFX::GetFontSize() const { return mFontSize; }
	unsigned int TextGFX::GetStartFontSize() const { return mStartFontSize; }

	Color TextGFX::GetColor() const { return mColor; }
	void TextGFX::SetColor(Color color) { mColor = color; }

	unsigned int TextGFX::GetTexId() const { return mTexture->GetId(); }
	void TextGFX::SetTextureSlot(int slot) { mTexture->Bind(slot); }
	unsigned int TextGFX::GetItemCount() const { return mText.size(); }
	// Get the size in bytes for each glyph in the text (= 4 vertices * num of letters)
	unsigned int TextGFX::GetBufferSize() const { return 4 * sizeof(Vertex) * mText.size(); }

	// Set the vertex data before submitting to the renderer
	const std::vector<Vertex>& TextGFX::GetVertexData()
	{
		mVertices.clear();
		UpdateTransform();

		// Get font atlas dimensions
		float atlasWidth = mFont->GetAtlasWidth();
		float atlasHeight = mFont->GetAtlasHeight();
		// Set the SPACE width to be equal to the width of a dot '.'
		float spaceWidth = mFont->GetGlyphs().at('.')->width;
		// Find the text's starting position
		glm::vec2 pos = GetTextStartPos(spaceWidth);
		pos.y -= mFontSize;

		for (int i = 0; i < mText.size(); i++)
		{
			// Find the correct ASCII glyph for the current character
			int glyphIndex = (int)mText[i];
			auto glyph = mFont->GetGlyphs().at(glyphIndex);

			// Get the correct position and dimensions for the current character
			float glyphYPos = pos.y - (glyph->height - glyph->bearingY);
			float glyphXPos = pos.x;
			float glyphHeight = glyph->height;
			float glyphWidth = glyph->width;
			if (std::isspace(mText[i]))
				glyphWidth = spaceWidth;

			// Get the bounds of the glyph in the atlas
			float lBound = glyph->atlasCoordX;
			float bBound = glyphHeight;
			float rBound = lBound + glyphWidth;
			float tBound = 0;

			/// Create the glyphs's vertices and add them to the vector of vertices for the entire text
			/// Texture coordinates are flipped vertically
			// Bottom left corner
			CreateVertex(glyphXPos + glyph->bearingX, glyphYPos,
				lBound / atlasWidth, bBound / atlasHeight);
			// Bottom right corner
			CreateVertex(glyphXPos + 2 * glyph->bearingX + glyphWidth, glyphYPos,
				rBound / atlasWidth, bBound / atlasHeight);
			// Top right corner
			CreateVertex(glyphXPos + 2 * glyph->bearingX + glyphWidth, glyphYPos + glyphHeight,
				rBound / atlasWidth, tBound / atlasHeight);
			// Top left corner
			CreateVertex(glyphXPos + glyph->bearingX, glyphYPos + glyphHeight,
				lBound / atlasWidth, tBound / atlasHeight);

			UpdateGlyphPos(i, pos.x, pos.y, glyph->advanceX);
		}
		return mVertices;
	}

	void TextGFX::SetupFont()
	{
		// Get the correct font from the font manager
		mFont = mFontManager->Get(mFontName, mFontSize);
		// Create a texture using the pixel data generated for a font atlas
		mTexture.reset(new Texture(*mFont));
	}

	void TextGFX::CreateVertex(const float posX, const float posY, const float texX, const float texY)
	{
		float isText = 1.0f;

		Vertex v;
		v.position = { posX, posY, 1.0f };
		v.color = mColor.GetBase();
		v.texCoords = { texX, texY };
		v.texSlot = (float)mTexture->GetTexSlot();
		v.isText = isText;
		mVertices.emplace_back(v);
	}

	void TextGFX::UpdateGlyphPos(int& index, float& x, float& y, const float glyphAdvance) const
	{
		x += glyphAdvance;
		// If the next character is a space
		if (std::isspace(mText[index + 1]))
		{
			// Get the width of the next word
			unsigned int wordIndex = index + 2;
			unsigned int nextWordWidth = GetNextWordWidth(wordIndex);
			// If the next word doesn't fit inside the textbox
			if (x + nextWordWidth >= mTransform->GetScale().x *
				(mTransform->GetPos().x + mTransform->GetWidth()) - mFontSize)
			{
				// Start rendering words on the next line
				x = mTransform->GetScale().x * mTransform->GetPos().x + mOffset.x;
				y -= mFontSize;
				index++;
			}
		}
	}

	unsigned int TextGFX::GetNextWordWidth(unsigned int& glyphIndex) const
	{
		int nextSpaceIndex = -1;
		// Find the index in the text of the next space
		for (int i = glyphIndex; i <= mText.size(); i++)
		{
			// If this character is a space or this is the end of the string
			if (std::isspace(mText[i]) || i == mText.size())
			{
				nextSpaceIndex = i;
				break;
			}
		}
		unsigned int wordWidth = 0;
		for (int i = glyphIndex; i < nextSpaceIndex; i++)
		{
			// Find the correct ASCII glyph for the current character
			auto glyph = mFont->GetGlyphs().at(mText[i]);
			// Add the glyph width to the word width
			wordWidth += glyph->advanceX;
		}
		glyphIndex = nextSpaceIndex + 1;
		return wordWidth;
	}

	void TextGFX::FindTextDimens(float spaceWidth)
	{
		mTextDimens = { 0.0f, 0.0f };
		mOffset = { 0.0f, 0.0f };
		float lineWidth = 0.0f;
		unsigned int wordIndex = 0;
		while (wordIndex < mText.size())
		{
			// Get the width of the next word and set the index for the next word
			unsigned int nextWordWidth = GetNextWordWidth(wordIndex);
			// If the next word doesn't fit inside the textbox
			if (lineWidth + nextWordWidth >= mTransform->GetScale().x * mTransform->GetWidth())
			{
				// Keep the biggest line width
				if (lineWidth > mTextDimens.x)
					mTextDimens.x = lineWidth;
				// Add the next line's height
				mTextDimens.y += mFontSize;
				// Reset line width
				lineWidth = nextWordWidth;
			}
			else
			{
				lineWidth += nextWordWidth;
				lineWidth += spaceWidth;
			}
		}
		// Keep the biggest line width
		if (lineWidth > mTextDimens.x)
			mTextDimens.x = lineWidth;
		// Add the height of the last line
		mTextDimens.y += mFontSize;
	}

	glm::vec2 TextGFX::GetTextStartPos(float spaceWidth)
	{
		if (!mIsTextCentered)
			return { mTransform->GetScale().x * mTransform->GetPos().x,
			mTransform->GetScale().y * mTransform->GetPos().y + mTransform->GetScale().y * mTransform->GetHeight() };

		FindTextDimens(spaceWidth);
		mOffset.x = (mTransform->GetWidth() * mTransform->GetScale().x - mTextDimens.x) / 2;
		mOffset.y = (mTransform->GetHeight() * mTransform->GetScale().y - mTextDimens.y) / 2;
		float xPos = mTransform->GetPos().x * mTransform->GetScale().x + mOffset.x;
		float yPos = mTransform->GetPos().y * mTransform->GetScale().y + mOffset.y + mTextDimens.y;
		return { xPos, yPos };
	}
}
