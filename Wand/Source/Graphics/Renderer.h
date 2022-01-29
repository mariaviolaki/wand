#pragma once

#include "Core/Window.h"
#include "Drawable.h"

namespace wand::RenderManager
{
	void Init(Window* window);
	void Render();
}

namespace wand::Renderer
{
	void Draw(Drawable* drawable);
}
