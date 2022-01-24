#include "WandPCH.h"
#include "Rectangle.h"

namespace wand
{
	// STATIC VARIABLES
	const unsigned int Rectangle::sIndexCount = 6;
	const unsigned int Rectangle::sSize = 4 * sizeof(Vertex);

	// STATIC FUNCTIONS
	// Get the number of indices to render 1 rectangle (= 2 triangles)
	unsigned int Rectangle::GetIndexCount()	{ return sIndexCount; }
	// Get the size in bytes for 1 rectangle (= 4 vertices)
	unsigned int Rectangle::GetSize() { return sSize; }

	// Create buffer data for 4 vertices to form a rectangle
	Rectangle::Rectangle(glm::vec2 pos, glm::vec2 dimens, glm::vec4 color)
		: mPos(pos), mDimens(dimens), mColor(color), mVertices(new std::array<Vertex, 4>)
	{
		CreateVertexData();
	}

	std::array<Vertex, 4>* Rectangle::GetVertexData() const	{ return mVertices.get(); }

	void Rectangle::CreateVertexData()
	{
		// Bottom left corner
		mVertices.get()->at(0).position = {mPos.x, mPos.y, 0.0f};
		mVertices.get()->at(0).color = mColor;

		// Bottom right corner
		mVertices.get()->at(1).position = { mPos.x + mDimens.x, mPos.y, 0.0f };
		mVertices.get()->at(1).color = mColor;

		// Top right corner
		mVertices.get()->at(2).position = { mPos.x + mDimens.x, mPos.y + mDimens.y, 0.0f };
		mVertices.get()->at(2).color = mColor;

		// Top left corner
		mVertices.get()->at(3).position = { mPos.x, mPos.y + mDimens.y, 0.0f };
		mVertices.get()->at(3).color = mColor;
	}
}
