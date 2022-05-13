#pragma once

#include "Base/Texture.h"
#include "Base/Font.h"
#include "Drawable.h"
#include "FontManager.h"

namespace wand
{
	class TextGFX : public Drawable
	{
	public:
		TextGFX(const std::string& fontName, unsigned int fontSize, Color color);

		// Submit and concatenate a string with the existing text
		void Add(const std::string& newText);
		// Replace the stored text with an empty string
		void Clear();
		// Set the text to be centered or to start from the top left corner
		void SetCenteredText(bool isTextCentered);
		// Render text using a new font
		void SetFont(std::string fontName, unsigned int fontSize);
		// Get the maximum number of characters in a text object
		unsigned int GetMaxLength() const;

		std::string GetFontName() const;
		unsigned int GetFontSize() const;
		unsigned int GetStartFontSize() const;
		void SetFontManager(FontManager* fontManager);
		Color GetColor() const override;
		void SetColor(Color color) override;
		unsigned int GetTexId() const override;
		void SetTextureSlot(int slot) override;
		unsigned int GetItemCount() const override;
		unsigned int GetBufferSize() const override;
		const std::vector<Vertex>& GetVertexData() override;

	private:
		FontManager* mFontManager;
		std::string mText;
		Color mColor;
		Font* mFont;
		std::string mFontName;
		unsigned int mFontSize;
		unsigned int mStartFontSize;
		std::shared_ptr<Texture> mTexture;
		std::vector<Vertex> mVertices;
		glm::vec2 mTextDimens;
		bool mIsTextCentered;
		glm::vec2 mOffset;

		void SetupFont();
		void CreateVertex(const float posX, const float posY, const float texX, const float texY);
		void UpdateGlyphPos(const int index, float& x, float& y, const float glyphAdvance) const;
		// Get the width of the next word and set its starting index
		unsigned int GetNextWordWidth(unsigned int& index) const;
		void FindTextDimens(float spaceWidth);
		glm::vec2 GetTextStartPos(float spaceWidth);
	};
}
