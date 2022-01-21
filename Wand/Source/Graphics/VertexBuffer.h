#pragma once

#include <memory>
#include "VertexLayout.h"

namespace wand
{
	class VertexBuffer
	{
	public:
		VertexBuffer(const float* vertices, unsigned int size);
		~VertexBuffer();
		
		void AddLayout(VertexLayout* layout);
		VertexLayout* GetLayout() const;
		void Bind() const;
		void Unbind() const;

	private:
		unsigned int mId;
		std::shared_ptr<VertexLayout> mLayout;
	};
}
