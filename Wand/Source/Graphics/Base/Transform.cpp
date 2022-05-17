#include "WandPCH.h"
#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"

namespace wand
{
	Transform::Transform()
		: mPos(glm::vec2(1.0f)), mScale(glm::vec2(1.0f)), mDimens({ 100.0f, 100.0f }),
		mRotation(0.0f), mFlipAxis(FlipAxis::FLIP_NONE), mLayer(0.0f), mIsLayoutChild(false)
	{}

	/******************** ACCESSOR METHODS ***********************/
	Vector2 Transform::GetPos() const { return { mPos.x, mPos.y }; }
	Vector2 Transform::GetScale() const { return { mScale.x, mScale.y }; }
	float Transform::GetLayer() const
	{
		// Layout children should be displayed on top of parents
		if (mIsLayoutChild)
			return mLayer + 0.1;
		return mLayer;
	}
	float Transform::GetWidth() const { return mDimens.x; }
	float Transform::GetHeight() const { return mDimens.y; }
	float Transform::GetRotation() const { return mRotation; }
	FlipAxis Transform::GetFlip() const { return mFlipAxis; }

	Vector2 Transform::GetTransformedPos(float x, float y)
	{
		// Create a rotation matrix
		// Rotate by the number of degrees set
		glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), glm::radians(mRotation), glm::vec3(0.0f, 0.0f, 1.0f));
		// Flip according to the flip axis/axes set
		switch (mFlipAxis)
		{
		case FlipAxis::FLIP_X:
			rotMat = glm::rotate(rotMat, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			break;
		case FlipAxis::FLIP_Y:
			rotMat = glm::rotate(rotMat, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			break;
		case FlipAxis::FLIP_XY:
			rotMat = glm::rotate(rotMat, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			rotMat = glm::rotate(rotMat, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			break;
		}
		// Get the new position, rotated around the object's center
		glm::vec2 endPos = glm::vec2((2 * mPos.x + mDimens.x) * mScale.x, (2 * mPos.y + mDimens.y) * mScale.y);
		glm::vec4 rotPos =
			rotMat * glm::vec4(glm::vec3(x, y, 0.0f) - glm::vec3(endPos.x / 2, endPos.y / 2, 0.0f), 1.0f);
		glm::vec3 pos = glm::vec3(rotPos) + glm::vec3(endPos.x / 2, endPos.y / 2, 0.0f);
		return { pos.x, pos.y };
	}

	/******************** MUTATOR METHODS ************************/
	void Transform::SetPos(float x, float y) { mPos = glm::vec2(x, y); }
	void Transform::SetScale(float x, float y) { mScale = glm::vec2(x, y); }
	void Transform::SetLayer(float layer) { mLayer = layer; }
	void Transform::SetWidth(float width) { mDimens.x = width; }
	void Transform::SetHeight(float height) { mDimens.y = height; }
	void Transform::SetRotation(float rotation) { mRotation = rotation; }
	void Transform::SetFlip(FlipAxis flipAxis) { mFlipAxis = flipAxis; }
	void Transform::SetLayoutChild(bool isLayoutChild) { mIsLayoutChild = isLayoutChild; }
}
