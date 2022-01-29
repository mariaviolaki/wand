#pragma once

#include "glm/glm.hpp"

namespace wand
{
	class Transform
	{
	public:
		Transform();

		glm::vec3 GetPosition() const;
		float GetWidth() const;
		float GetHeight() const;

		void SetPosition(float x, float y);
		void SetWidth(float width);
		void SetHeight(float height);

	private:
		glm::mat4 mTransform;
		float mWidth;
		float mHeight;
	};
}