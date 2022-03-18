#include "WandPCH.h"
#include "Rectangle.h"

namespace wand
{
	Rectangle::Rectangle(glm::vec4 color)
		: UIComponent(false), drawable(std::make_shared<RectangleGFX>(color))
	{
		SetTransform(drawable->GetTransform());
	}

	Drawable* Rectangle::GetDrawable() const { return drawable.get(); }
}
