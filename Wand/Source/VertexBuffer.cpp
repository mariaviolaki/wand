#include "VertexBuffer.h"

#include "glad/glad.h"

namespace wand
{
	VertexBuffer::VertexBuffer(const float* vertices, unsigned int size)
	{
		// Create a buffer object and assign it an id
		glGenBuffers(1, &mId);
		// Set the buffer as the current vertex buffer object
		glBindBuffer(GL_ARRAY_BUFFER, mId);
		// Add the given vertex data to the VBO
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &mId);
	}

	void VertexBuffer::AddLayout(VertexLayout* layout)
	{
		mLayout.reset(layout);
	}

	VertexLayout* VertexBuffer::GetLayout() const
	{
		return mLayout.get();
	}

	void VertexBuffer::Bind() const
	{
		// Set the buffer as the current vertex buffer object
		glBindBuffer(GL_ARRAY_BUFFER, mId);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
