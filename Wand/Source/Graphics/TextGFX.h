#pragma once

#include "Base/Texture.h"
#include "Base/Font.h"
#include "Drawable.h"

namespace wand
{
	class TextGFX : public Drawable
	{
	public:
		TextGFX(const std::string& fontName, unsigned int fontSize, const glm::vec4& color);

		void Add(const std::string& newText);
		void Clear();
		unsigned int GetMaxLength() const;

		glm::vec4 GetColor() const override;
		void SetColor(glm::vec4 color) override;

		unsigned int GetTexId() const override;
		void SetTextureSlot(int slot) override;
		unsigned int GetItemCount() const override;
		unsigned int GetBufferSize() const override;
		const std::vector<Vertex>& GetVertexData() override;

	private:
		std::string mText;
		glm::vec4 mColor;
		Font* mFont;
		unsigned int mLineHeight;
		std::shared_ptr<Texture> mTexture;
		std::vector<Vertex> mVertices;

		void CreateVertex(const float posX, const float posY, const float texX, const float texY);
		void UpdateGlyphPos(int& index, float& x, float& y, const float glyphAdvance) const;
		unsigned int GetNextWordWidth(const int index) const;
	};
}
