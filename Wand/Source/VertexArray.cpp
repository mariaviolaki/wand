#include "VertexArray.h"

#include "glad/glad.h"

namespace wand
{
	VertexArray::VertexArray()
	{
		// Create a vertex array and assign it an id
		glGenVertexArrays(1, &mId);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &mId);
	}

	void VertexArray::Config(const VertexBuffer& buffer) const
	{
		glBindVertexArray(mId);
		buffer.Bind();

		// Get all the different attributes included in a single vertex buffer
		VertexLayout* layout = buffer.GetLayout();
		std::vector<VertexAttribute> attributes = layout->GetAttributes();

		// Repeat for every vertex attribute (e.g.: position, color, etc.)
		for (int i = 0; i < attributes.size(); i++)
		{
			// Enable the specific attribute
			glEnableVertexAttribArray(i);
			// Add a description about the vertex attribute
			glVertexAttribPointer(i, 
				attributes[i].count, 
				attributes[i].type, 
				attributes[i].normalized,
				layout->GetStride(), 
				(const void*)attributes[i].offset);
		}
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(mId);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
}
