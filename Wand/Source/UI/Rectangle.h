#pragma once

#include "Graphics/RectangleGFX.h"
#include "UIEntity.h"

namespace wand
{
	class Rectangle : public UIEntity
	{
	public:
		Rectangle(glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f });
		Drawable* GetDrawable() const override;

	private:
		std::shared_ptr<RectangleGFX> drawable;
	};
}
