#include "IndexBuffer.h"

#include "glad/glad.h"

namespace wand
{
	IndexBuffer::IndexBuffer(const unsigned int* indices, unsigned int count)
		: mCount(count)
	{
		// Create a buffer object and assign it an id
		glGenBuffers(1, &mId);
		// Set the buffer as the current index buffer object
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
		// Add the given index data to the IBO
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &mId);
	}

	unsigned int IndexBuffer::GetCount() const
	{
		return mCount;
	}

	void IndexBuffer::Bind() const
	{
		// Set the buffer as the current index buffer object
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
