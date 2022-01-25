#include "WandPCH.h"
#include "Rectangle.h"

namespace wand
{
	Rectangle::Rectangle(glm::vec4 color)
		: Drawable(), mVertices(std::make_shared<std::array<Vertex, 4>>()), mColor(color)
	{
		SetWidth(10.0f);
		SetHeight(10.0f);
	}

	std::array<Vertex, 4>* Rectangle::GetVertexData()
	{
		// Bottom left corner
		mVertices.get()->at(0).position = 
		{ 
			GetPosition().x, GetPosition().y, GetPosition().z 
		};
		mVertices.get()->at(0).color = mColor;

		// Bottom right corner
		mVertices.get()->at(1).position =
		{
			GetPosition().x + GetWidth(), GetPosition().y, GetPosition().z
		};
		mVertices.get()->at(1).color = mColor;

		// Top right corner
		mVertices.get()->at(2).position =
		{
			GetPosition().x + GetWidth(), GetPosition().y + GetHeight(), GetPosition().z
		};
		mVertices.get()->at(2).color = mColor;

		// Top left corner
		mVertices.get()->at(3).position =
		{
			GetPosition().x, GetPosition().y + GetHeight(), GetPosition().z
		};
		mVertices.get()->at(3).color = mColor;

		return mVertices.get();
	}
}
