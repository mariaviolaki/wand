#pragma once

#include "Graphics.h"

namespace wand
{
	class IndexBuffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

	private:
		unsigned int mId;
		std::unique_ptr<std::array<unsigned int, MAX_INDICES>> mIndices;

		void CreateMaxIndexData();
	};
}
