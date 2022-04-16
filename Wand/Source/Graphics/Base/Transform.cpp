#include "WandPCH.h"
#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"

namespace wand
{
	Transform::Transform(glm::vec2 dimens)
		: mTransform(glm::mat4(1.0f)), mScale(glm::vec2(1.0f)), mDimens(dimens), mDepth(0.0f)
	{}

	/******************** ACCESSOR METHODS ***********************/

	const glm::vec2& Transform::GetPosition() const { return mScale * glm::vec2({ mTransform[3] }); }

	const glm::vec2& Transform::GetScale() const { return mScale; }

	float Transform::GetDepth() const { return mDepth; }

	float Transform::GetWidth() const { return mScale.x * mDimens.x; }

	float Transform::GetHeight() const { return mScale.y * mDimens.y; }

	/******************** MUTATOR METHODS ************************/

	void Transform::SetPosition(float x, float y) { mTransform = glm::translate(mTransform, glm::vec3(x, y, 0.0f)); }

	void Transform::SetScale(float x, float y) { mScale = glm::vec2(x, y); }

	void Transform::SetDepth(float depth) { mDepth = depth; }

	void Transform::SetWidth(float width) { mDimens.x = width; }

	void Transform::SetHeight(float height) { mDimens.y = height; }
}
