#include "WandPCH.h"
#include "Rectangle.h"

namespace wand
{
	Rectangle::Rectangle(glm::vec4 color)
		: RectangleGFX(color), UIComponent(GetTransform(), false)
	{}
}
