#pragma once

#include "Drawable.h"
#include "Base/Texture.h"

namespace wand
{
	class Sprite : public Drawable
	{
	public:
		Sprite(const std::string& imagePath);

		unsigned int GetTexId() const override;
		void SetTextureSlot(int slot) override;
		unsigned int GetItemCount() const override;
		unsigned int GetBufferSize() const override;
		const std::vector<Vertex>& GetVertexData() override;

	private:
		std::shared_ptr<Texture> mTexture;
		std::vector<Vertex> mVertices;

		void CreateVertex(const float posX, const float posY, const float texX, const float texY);
	};
}
