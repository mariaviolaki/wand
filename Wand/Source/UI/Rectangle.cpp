#include "WandPCH.h"
#include "Rectangle.h"

namespace wand
{
	Rectangle::Rectangle(glm::vec4 color)
		: UIEntity(false), drawable(std::make_shared<RectangleGFX>(color))
	{}

	Drawable* Rectangle::GetDrawable() const { return drawable.get(); }
	Transform* Rectangle::GetTransform() const { return drawable->GetTransform(); }
}
