#pragma once

#include "Graphics.h"

namespace wand
{
	class VertexLayout
	{
	public:
		VertexLayout();

		// Add a new attribute to the vertex buffer layout
		void AddFloats(unsigned int count);

		const std::vector<VertexAttribute>& GetAttributes() const;
		// Get the size (in bytes) of the entire vertex
		unsigned int GetStride() const;

	private:
		std::vector<VertexAttribute> mAttributes;
		unsigned int mStride;
	};
}
