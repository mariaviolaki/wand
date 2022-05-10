#pragma once

#include "VertexLayout.h"

namespace wand
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void AddLayout(VertexLayout* layout); // should be called after binding a vertex buffer
		void Bind() const;
		void Unbind() const;

	private:
		unsigned int mId;
		std::unique_ptr<VertexLayout> mLayout;
	};
}
