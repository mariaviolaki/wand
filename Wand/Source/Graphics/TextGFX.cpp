#include "WandPCH.h"
#include "TextGFX.h"
#include "FontManager.h"
#include "Core/Window.h"

namespace wand
{
	TextGFX::TextGFX(const std::string& fontName, unsigned int fontSize, const glm::vec4& color)
		: Drawable(), mFont(FontManager::Get(fontName, fontSize)),
		mColor(color), mText(""), mTexture(nullptr), mVertices()
	{
		// Create a texture using the pixel data generated for a font atlas
		mTexture = std::make_shared<Texture>(*mFont);
		// Set the line height for the given font
		mLineHeight = mFont->GetSize();
	}

	// Submit and concatenate a string with the existing text
	void TextGFX::Add(const std::string& newText)
	{
		if (mText.size() + newText.size() <= MAX_TEXT_LENGTH)
			mText += newText;
		else
			std::cout << "Submitted text exceeds max character limit.\n";
	}

	// Replace the stored text with an empty string
	void TextGFX::Clear() { mText = ""; }

	// Get the maximum number of characters in a text object
	unsigned int TextGFX::GetMaxLength() const	{ return MAX_TEXT_LENGTH; }

	glm::vec4 TextGFX::GetColor() const { return mColor; }
	void TextGFX::SetColor(glm::vec4 color) { mColor = color; }

    unsigned int TextGFX::GetTexId() const { return mTexture->GetId(); }
	void TextGFX::SetTextureSlot(int slot) { mTexture->Bind(slot); }
	unsigned int TextGFX::GetItemCount() const	{ return mText.size(); }
	// Get the size in bytes for each glyph in the text (= 4 vertices * num of letters)
	unsigned int TextGFX::GetBufferSize() const { return 4 * sizeof(Vertex) * mText.size(); }

	// Set the vertex data before submitting to the renderer
	const std::vector<Vertex>& TextGFX::GetVertexData()
	{
		mVertices.clear();
		// Get font atlas dimensions
		float atlasWidth = mFont->GetAtlasWidth();
		float atlasHeight = mFont->GetAtlasHeight();
		// Get text position
		Transform* t = GetTransform().get();
		glm::vec3 pos = { t->GetPosition().x, t->GetHeight(), t->GetDepth() };
		pos.y -= mLineHeight;
		
		// Set the SPACE width to be equal to the width of a dot '.'
		float spaceWidth = mFont->GetGlyphs().at('.')->width;		

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
			CreateVertex(glyphXPos + glyph->bearingX + glyphWidth, glyphYPos,
				rBound / atlasWidth, bBound / atlasHeight);
			// Top right corner
			CreateVertex(glyphXPos + glyph->bearingX + glyphWidth, glyphYPos + glyphHeight,
				rBound / atlasWidth, tBound / atlasHeight);
			// Top left corner
			CreateVertex(glyphXPos + glyph->bearingX, glyphYPos + glyphHeight,
				lBound / atlasWidth, tBound / atlasHeight);

			UpdateGlyphPos(i, pos.x, pos.y, glyph->advanceX);
		}
		return mVertices;
	}

	void TextGFX::CreateVertex(const float posX, const float posY, const float texX, const float texY)
	{
		float isText = 1.0f;

		Vertex v;
		v.position = { posX, posY, 1.0f };
		v.color = mColor;
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
			unsigned int nextWordWidth = GetNextWordWidth(index + 2);
			// If the next word doesn't fit inside the textbox
			if (x + nextWordWidth >= GetTransform()->GetWidth())
			{
				// Start rendering words on the next line
				x = GetTransform()->GetPosition().x;
				y -= mLineHeight;
				index++;
			}
		}
	}

	unsigned int TextGFX::GetNextWordWidth(const int glyphIndex) const
	{
		int nextSpaceIndex = -1;
		// Find the index in the text of the next space
		for (int i = glyphIndex; i <= mText.size(); i++)
		{
			// If this is the end of the string or this character is a space
			if (i == mText.size() || std::isspace(mText[i]))
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
		return wordWidth;
	}
}
