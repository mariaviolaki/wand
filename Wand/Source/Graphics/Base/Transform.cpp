#include "WandPCH.h"
#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"

namespace wand
{
	Transform::Transform(bool isLayoutChild)
		: mTransform(glm::mat4(1.0f)), mScale(glm::vec2(1.0f)), mDimens({ 100.0f, 100.0f }),
		mDepth(0.0f), mIsLayoutChild(isLayoutChild)
	{}

	/******************** ACCESSOR METHODS ***********************/

	const glm::vec2& Transform::GetPos() const { return glm::vec2({ mTransform[3] }); }

	const glm::vec2& Transform::GetScale() const { return mScale; }

	float Transform::GetDepth() const
	{
		// Layout children should be displayed on top of parents
		if (mIsLayoutChild)
			return mDepth + 0.5;
		return mDepth;
	}

	float Transform::GetWidth() const { return mDimens.x; }

	float Transform::GetHeight() const { return mDimens.y; }

	/******************** MUTATOR METHODS ************************/

	void Transform::SetPos(float x, float y) { mTransform = glm::translate(mTransform, glm::vec3(x, y, 0.0f)); }

	void Transform::SetScale(float x, float y) { mScale = glm::vec2(x, y); }

	void Transform::SetDepth(float depth) { mDepth = depth; }

	void Transform::SetWidth(float width) { mDimens.x = width; }

	void Transform::SetHeight(float height) { mDimens.y = height; }
}
