#include "WandPCH.h"
#include "Transform.h"

namespace wand
{
	Transform::Transform(glm::vec2 dimens)
		: mPosition(0.0f, 0.0f, 1.0f), mScale(dimens)
	{}

	/******************** ACCESSOR METHODS ***********************/

	const glm::vec3& Transform::GetPosition() const { return mPosition; }

	float Transform::GetWidth() const { return mScale.x; }

	float Transform::GetHeight() const { return mScale.y; }

	/******************** MUTATOR METHODS ************************/

	void Transform::SetPosition(float x, float y) { mPosition = glm::vec3(x, y, 1.0f); }

	void Transform::SetWidth(float width) { mScale.x = width; }

	void Transform::SetHeight(float height) { mScale.y = height; }
}
