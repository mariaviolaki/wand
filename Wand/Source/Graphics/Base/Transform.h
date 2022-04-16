#pragma once

#include "glm/glm.hpp"

namespace wand
{
	class Transform
	{
	public:
		Transform(glm::vec2 dimens = { 100.0f, 100.0f });

		const glm::vec2& GetPosition() const;
		const glm::vec2& GetScale() const;
		float GetDepth() const;
		float GetWidth() const;
		float GetHeight() const;

		void SetPosition(float x, float y);
		void SetScale(float x, float y);
		void SetDepth(float depth);
		void SetWidth(float width);
		void SetHeight(float height);

	private:
		glm::mat4 mTransform;
		glm::vec2 mScale;
		glm::vec2 mDimens;
		float mDepth;
	};
}
