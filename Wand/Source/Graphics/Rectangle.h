#pragma once

#include "Drawable.h"
#include "Graphics.h"

namespace wand
{
	class Rectangle : public Drawable
	{
	public:
		Rectangle(glm::vec4 color);
		std::array<Vertex, 4>* GetVertexData() override;

	private:
		glm::vec4 mColor;
		std::shared_ptr<std::array<Vertex, 4>> mVertices;
	};
}
