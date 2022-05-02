#pragma once

#include "Graphics/RectangleGFX.h"
#include "UIEntity.h"

namespace wand
{
	class Rectangle : public UIEntity
	{
	public:
		Rectangle(Color color = Color(255, 255, 255, 0));
		Drawable* GetDrawable() const override;
		Transform* GetTransform() const override;

	private:
		std::shared_ptr<RectangleGFX> drawable;
	};
}
