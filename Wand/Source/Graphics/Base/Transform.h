#pragma once

#include "glm/glm.hpp"

namespace wand
{
	class Transform
	{
	public:
		Transform(bool isLayoutChild = false);

		const glm::vec2& GetPos() const;
		const glm::vec2& GetScale() const;
		float GetDepth() const;
		float GetWidth() const;
		float GetHeight() const;

		void SetPos(float x, float y);
		void SetScale(float x, float y);
		void SetDepth(float depth);
		void SetWidth(float width);
		void SetHeight(float height);

	private:
		glm::mat4 mTransform;
		glm::vec2 mScale;
		glm::vec2 mDimens;
		float mDepth;
		bool mIsLayoutChild;
	};
}
