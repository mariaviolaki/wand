#pragma once

#include <memory>
#include <array>
#include "Graphics.h"
#include "VertexLayout.h"

namespace wand
{
	class Rectangle
	{
	public:
		static unsigned int GetIndexCount();
		static unsigned int GetSize();

		Rectangle(glm::vec2 pos, glm::vec2 dimens, glm::vec4 color);

		std::array<Vertex, 4>* GetVertexData() const;

	private:
		static const unsigned int sIndexCount;
		static const unsigned int sSize;

		glm::vec2 mPos;
		glm::vec2 mDimens;
		glm::vec4 mColor;
		std::unique_ptr<std::array<Vertex, 4>> mVertices;

		void CreateVertexData();
	};
}
