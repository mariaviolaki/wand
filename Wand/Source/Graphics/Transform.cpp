#include "WandPCH.h"
#include "Transform.h"

#include "glm/gtc/matrix_transform.hpp"

namespace wand
{
	Transform::Transform()
		: mTransform(glm::mat4(1.0f)), mWidth(10.0f), mHeight(10.0f)
	{}

	/******************** ACCESSOR METHODS ***********************/

	glm::vec3 Transform::GetPosition() const { return glm::vec3({ mTransform[3] }); }

	float Transform::GetWidth() const { return mWidth; }

	float Transform::GetHeight() const { return mHeight; }

	/******************** MUTATOR METHODS ************************/

	void Transform::SetPosition(float x, float y)
	{
		mTransform = glm::translate(mTransform, glm::vec3(x, y, 0.0f));
	}

	void Transform::SetWidth(float width) { mWidth = width; }

	void Transform::SetHeight(float height) { mHeight = height; }
}
