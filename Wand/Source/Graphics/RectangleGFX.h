#pragma once

#include "Drawable.h"
#include "Graphics.h"
#include "Base/Texture.h"
#include "Color.h"

namespace wand
{
	class RectangleGFX : public Drawable
	{
	public:
		RectangleGFX(Color color);

		Color GetColor() const override;
		void SetColor(Color color) override;
		unsigned int GetItemCount() const override;
		unsigned int GetBufferSize() const override;
		const std::vector<Vertex>& GetVertexData() override;

	private:
		Color mColor;
		std::shared_ptr<Texture> mTexture;
		std::vector<Vertex> mVertices;

		void CreateVertex(const float posX, const float posY, const float texX, const float texY);
	};
}
