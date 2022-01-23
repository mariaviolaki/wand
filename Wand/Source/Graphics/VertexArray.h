#pragma once

#include <memory>
#include "VertexLayout.h"

namespace wand
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		// Should be called after binding a vertex buffer
		void AddLayout(VertexLayout* layout);
		void Bind() const;
		void Unbind() const;

	private:
		unsigned int mId;
		std::unique_ptr<VertexLayout> mLayout;
	};
}
