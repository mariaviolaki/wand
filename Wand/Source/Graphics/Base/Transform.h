#pragma once

#include "glm/glm.hpp"

namespace wand
{
	struct Vector2
	{
		float x;
		float y;
	};

	enum class FlipAxis { FLIP_NONE, FLIP_X, FLIP_Y, FLIP_XY };


	class Transform
	{
	public:
		Transform();

		Vector2 GetPos() const;
		Vector2 GetScale() const;
		float GetLayer() const;
		float GetWidth() const;
		float GetHeight() const;
		float GetRotation() const;
		FlipAxis GetFlip() const;
		// Change the given position according to the saved rotation/flip axis
		Vector2 GetTransformedPos(float x, float y);

		void SetPos(float x, float y);
		void SetScale(float x, float y);
		void SetLayer(float layer);
		void SetWidth(float width);
		void SetHeight(float height);
		void SetRotation(float rotation);
		void SetFlip(FlipAxis flipAxis);
		void SetLayoutChild(bool isLayoutChild);

	private:
		glm::vec2 mPos;
		glm::vec2 mScale;
		glm::vec2 mDimens;
		float mRotation;
		FlipAxis mFlipAxis;
		float mLayer;
		bool mIsLayoutChild;
	};
}
