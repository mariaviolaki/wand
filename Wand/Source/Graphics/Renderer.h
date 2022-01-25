#pragma once

#include "Core/Window.h"
#include "Graphics.h"
#include "Drawable.h"

namespace wand::RenderManager
{
	void Init(Window* window);
	void Render();
}

namespace wand::Renderer
{
	void Draw(std::shared_ptr<Drawable> drawable);
}
