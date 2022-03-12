#pragma once

#include "Drawable.h"
#include "Graphics.h"
#include "Base/Texture.h"

namespace wand
{
	class RectangleGFX : public Drawable
	{
	public:
		RectangleGFX(glm::vec4 color);

		glm::vec4 GetColor() const override;
		void SetColor(glm::vec4 color) override;
		unsigned int GetItemCount() const override;
		unsigned int GetBufferSize() const override;
		const std::vector<Vertex>& GetVertexData() override;

	private:
		glm::vec4 mColor;
		std::shared_ptr<Texture> mTexture;
		std::vector<Vertex> mVertices;

		void CreateVertex(const float posX, const float posY, const float texX, const float texY);
	};
}
