#include "WandPCH.h"
#include "SpriteGFX.h"

namespace wand
{
	SpriteGFX::SpriteGFX(const std::string& imagePath)
		: mTexture(std::make_shared<Texture>(std::filesystem::current_path().string() + "\\" + imagePath)),
		mVertices()
	{}

	unsigned int SpriteGFX::GetTexId() const { return mTexture->GetId(); }

	void SpriteGFX::SetTextureSlot(int slot) { mTexture->Bind(slot); }

	unsigned int SpriteGFX::GetItemCount() const {	return 1; }

	// Get the size in bytes for 1 sprite (= 4 vertices)
	unsigned int SpriteGFX::GetBufferSize() const { return 4  * sizeof(Vertex); }

	// Set the vertex data before submitting to the renderer
	const std::vector<Vertex>& SpriteGFX::GetVertexData()
	{
		// Bottom left corner
		CreateVertex(GetPosition().x, GetPosition().y, 0.0f, 0.0f);
		// Bottom right corner
		CreateVertex(GetPosition().x + GetWidth(), GetPosition().y, 1.0f, 0.0f);
		// Top right corner
		CreateVertex(GetPosition().x + GetWidth(), GetPosition().y + GetHeight(), 1.0f, 1.0f);
		// Top left corner
		CreateVertex(GetPosition().x, GetPosition().y + GetHeight(), 0.0f, 1.0f);

		return mVertices;
	}

	void SpriteGFX::CreateVertex(const float posX, const float posY, const float texX, const float texY)
	{
		glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f }; // solid white for sprites
		float isText = 0.0f;

		Vertex v;
		v.position = { posX, posY, GetDepth() };
		v.color = color;
		v.texCoords = { texX, texY };
		v.texSlot = (float)mTexture->GetTexSlot();
		v.isText = isText;
		mVertices.emplace_back(v);
	}
}
