#include "WandPCH.h"
#include "Rectangle.h"

namespace wand
{
	Rectangle::Rectangle(glm::vec4 color)
		: mColor(color), mTexture(std::make_shared<Texture>()), 
		mVertices()
	{}

	glm::vec4 Rectangle::GetColor() const { return mColor; }

	void Rectangle::SetColor(glm::vec4 color) { mColor = color; }

	unsigned int Rectangle::GetItemCount() const { return 1; }

	// Get the size in bytes for 1 rectangle (= 4 vertices)
	unsigned int Rectangle::GetBufferSize() const { return 4 * sizeof(Vertex); }

	// Set the vertex data before submitting to the renderer
	const std::vector<Vertex>& Rectangle::GetVertexData()
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

	void Rectangle::CreateVertex(const float posX, const float posY, const float texX, const float texY)
	{
		float texSlot = 0.0f; // rectangles have no actual texture
		float isText = 0.0f;

		Vertex v;
		v.position = { posX, posY, GetPosition().z };
		v.color = mColor;
		v.texCoords = { texX, texY };
		v.texSlot = texSlot;
		v.isText = isText;
		mVertices.emplace_back(v);
	}
}
