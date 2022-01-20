#pragma once

#include <vector>
#include "glad/glad.h"

namespace wand
{
	struct VertexAttribute
	{
		unsigned int count;
		unsigned int type;
		unsigned int normalized;
		unsigned int offset;
	};

	class VertexLayout
	{
	public:
		VertexLayout();

		// Add a new attribute to the vertex buffer layout
		template<typename T>
		void Add(unsigned int count);
		template<>
		void Add<float>(unsigned int count);

		const std::vector<VertexAttribute>& GetAttributes() const;
		// Get the size (in bytes) of the entire vertex
		unsigned int GetStride() const;

	private:
		std::vector<VertexAttribute> mAttributes;
		unsigned int mStride;
	};
}
