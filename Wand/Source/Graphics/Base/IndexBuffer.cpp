#include "WandPCH.h"
#include "IndexBuffer.h"

#include "glad/glad.h"

namespace wand
{
	IndexBuffer::IndexBuffer()
		: mIndices(new std::array<unsigned int, MAX_INDICES>)
	{
		// Create a buffer object and assign it an id
		glGenBuffers(1, &mId);
		// Set the buffer as the current index buffer object
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
		// Create and add the index data to the IBO
		CreateMaxIndexData();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_INDICES * sizeof(unsigned int), mIndices.get()->data(), GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &mId);
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

	// Create and poplulate an array of indices
	void IndexBuffer::CreateMaxIndexData()
	{
		// Repeat for each rectangle
		for (unsigned int i = 0, offset = 0; i < MAX_INDICES; i += 6, offset += 4)
		{
			// Indices for 1st triangle
			mIndices.get()->at(i + 0) = offset + 0;
			mIndices.get()->at(i + 1) = offset + 1;
			mIndices.get()->at(i + 2) = offset + 2;
			// Indices for 2nd triangle
			mIndices.get()->at(i + 3) = offset + 2;
			mIndices.get()->at(i + 4) = offset + 3;
			mIndices.get()->at(i + 5) = offset + 0;
		}
	}
}
