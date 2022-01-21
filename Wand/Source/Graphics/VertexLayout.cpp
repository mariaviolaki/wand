#include "VertexLayout.h"

namespace wand
{
	VertexLayout::VertexLayout()
		: mStride(0)
	{}

	template<>
	void VertexLayout::Add<float>(unsigned int count)
	{
		mAttributes.push_back({ count, GL_FLOAT, GL_FALSE, mStride });
		mStride += count * sizeof(float);
	}

	const std::vector<VertexAttribute>& VertexLayout::GetAttributes() const
	{
		return mAttributes;
	}

	unsigned int VertexLayout::GetStride() const
	{
		return mStride;
	}
}