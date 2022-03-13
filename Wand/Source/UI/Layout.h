#pragma once

#include "Graphics/Base/Transform.h"

namespace wand
{
	enum class LayoutPosition 
	{
		LEFT, CENTERX, RIGHT, // horizontal
		BOTTOM, CENTERY, TOP  // vertical
	};

	class Layout
	{
	public:
		Layout();

		glm::vec3 GetPosition() const;
		float GetWidth() const;
		float GetHeight() const;
		void SetPosition(float x, float y);
		void SetWidth(float width);
		void SetHeight(float height);

	private:
		std::shared_ptr<Transform> mTransform;
	};
}
