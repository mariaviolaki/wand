#include "WandPCH.h"
#include "SpriteGFX.h"

namespace wand
{
	SpriteGFX::SpriteGFX(const std::string& imagePath)
		: mTexture(std::make_shared<Texture>(imagePath)), mVertices()
	{
		mTransform->SetWidth(mTexture->GetWidth());
		mTransform->SetHeight(mTexture->GetHeight());
	}

	unsigned int SpriteGFX::GetTexId() const { return mTexture->GetId(); }

	void SpriteGFX::SetTextureSlot(int slot) { mTexture->Bind(slot); }

	unsigned int SpriteGFX::GetItemCount() const { return 1; }

	// Get the size in bytes for 1 sprite (= 4 vertices)
	unsigned int SpriteGFX::GetBufferSize() const { return 4 * sizeof(Vertex); }

	// Set the vertex data before submitting to the renderer
	const std::vector<Vertex>& SpriteGFX::GetVertexData()
	{
		mVertices.clear();
		UpdateTransform();
		Transform& t = *mTransform.get();

		// Bottom left corner
		CreateVertex(t.GetPos().x * t.GetScale().x,
			t.GetPos().y * t.GetScale().y, 0.0f, 0.0f);
		// Bottom right corner
		CreateVertex(t.GetPos().x * t.GetScale().x + t.GetWidth() * t.GetScale().x,
			t.GetPos().y * t.GetScale().y, 1.0f, 0.0f);
		// Top right corner
		CreateVertex(t.GetPos().x * t.GetScale().x + t.GetWidth() * t.GetScale().x,
			t.GetPos().y * t.GetScale().y + t.GetHeight() * t.GetScale().y, 1.0f, 1.0f);
		// Top left corner
		CreateVertex(t.GetPos().x * t.GetScale().x,
			t.GetPos().y * t.GetScale().y + t.GetHeight() * t.GetScale().y, 0.0f, 1.0f);

		return mVertices;
	}

	void SpriteGFX::CreateVertex(const float posX, const float posY, const float texX, const float texY)
	{
		glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f }; // solid white for sprites
		float isText = 0.0f;
		Vector2 transformedPos = mTransform->GetTransformedPos(posX, posY);

		Vertex v;
		v.position = { transformedPos.x, transformedPos.y, 1.0f };
		v.color = color;
		v.texCoords = { texX, texY };
		v.texSlot = (float)mTexture->GetTexSlot();
		v.isText = isText;
		mVertices.emplace_back(v);
	}
}
