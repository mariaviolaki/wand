#include "WandPCH.h"
#include "Drawable.h"

#include "glm/gtc/matrix_transform.hpp"

namespace wand
{
	// STATIC VARIABLES
	const unsigned int Drawable::sIndexCount = 6;
	const unsigned int Drawable::sSize = 4 * sizeof(Vertex);

	// STATIC FUNCTIONS
	// Get the number of indices to render 1 rectangle (= 2 triangles)
	unsigned int Drawable::GetIndexCount() { return sIndexCount; }
	// Get the size in bytes for 1 rectangle (= 4 vertices)
	unsigned int Drawable::GetSize() { return sSize; }

	Drawable::Drawable()
		: mTransform(glm::mat4(1.0f)), mWidth(0.0f), mHeight(0.0f)
	{}

	glm::vec3 Drawable::GetPosition() const
	{
		return glm::vec3(mTransform[3]);
	}

	float Drawable::GetWidth() const { return mWidth; }

	float Drawable::GetHeight() const {	return mHeight;	}

	void Drawable::SetPosition(float x, float y)
	{
		mTransform = glm::translate(mTransform, glm::vec3(x, y, 0.0f));
	}

	void Drawable::SetWidth(float width) { mWidth = width; }

	void Drawable::SetHeight(float height) { mHeight = height; }
}
