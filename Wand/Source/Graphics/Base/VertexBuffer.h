#pragma once

namespace wand
{
	class VertexBuffer
	{
	public:
		VertexBuffer(const float* vertices, unsigned int size);
		~VertexBuffer();
		
		void Bind() const;
		void Unbind() const;

	private:
		unsigned int mId;
	};
}
