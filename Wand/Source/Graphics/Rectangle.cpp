#include "WandPCH.h"
#include "Rectangle.h"

namespace wand
{
	Rectangle::Rectangle(glm::vec4 color)
		: Drawable(color)
	{}

	void Rectangle::SetColor(glm::vec4 color) { Drawable::SetColor(color); }
}
