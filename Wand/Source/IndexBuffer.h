#pragma once

namespace wand
{
	class IndexBuffer
	{
	public:
		IndexBuffer(const unsigned int* indices, unsigned int count);
		~IndexBuffer();

		unsigned int GetCount() const;
		void Bind() const;
		void Unbind() const;

	private:
		unsigned int mId;
		unsigned int mCount;
	};
}
