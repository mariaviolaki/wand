#pragma once

#include "VertexBuffer.h"

namespace wand
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Config(const VertexBuffer& buffer) const;
		void Bind() const;
		void Unbind() const;

	private:
		unsigned int mId;
	};
}
