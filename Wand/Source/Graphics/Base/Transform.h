#pragma once

#include "glm/glm.hpp"

namespace wand
{
	struct Vector2
	{
		float x;
		float y;
	};

	class Transform
	{
	public:
		Transform();

		Vector2 GetPos() const;
		Vector2 GetScale() const;
		float GetLayer() const;
		float GetWidth() const;
		float GetHeight() const;

		void SetPos(float x, float y);
		void SetScale(float x, float y);
		void SetLayer(float layer);
		void SetWidth(float width);
		void SetHeight(float height);
		void SetLayoutChild(bool isLayoutChild);

	private:
		glm::vec2 mPos;
		glm::vec2 mScale;
		glm::vec2 mDimens;
		float mLayer;
		bool mIsLayoutChild;
	};
}
