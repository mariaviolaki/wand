#include "WandPCH.h"
#include "Transform.h"

namespace wand
{
	Transform::Transform()
		: mPos(glm::vec2(1.0f)), mScale(glm::vec2(1.0f)), mDimens({ 100.0f, 100.0f }),
		mLayer(0.0f), mIsLayoutChild(false)
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

	/******************** MUTATOR METHODS ************************/
	void Transform::SetPos(float x, float y) { mPos = glm::vec2(x, y); }
	void Transform::SetScale(float x, float y) { mScale = glm::vec2(x, y); }
	void Transform::SetLayer(float layer) { mLayer = layer; }
	void Transform::SetWidth(float width) { mDimens.x = width; }
	void Transform::SetHeight(float height) { mDimens.y = height; }
	void Transform::SetLayoutChild(bool isLayoutChild) { mIsLayoutChild = isLayoutChild; }
}
