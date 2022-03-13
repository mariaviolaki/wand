#pragma once

#include "Graphics/RectangleGFX.h"
#include "UIComponent.h"

namespace wand
{
	class Rectangle : public RectangleGFX, public UIComponent
	{
	public:
		Rectangle(glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f });
	};
}