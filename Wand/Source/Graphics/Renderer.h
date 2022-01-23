#pragma once

#include "Graphics.h"

namespace wand::RenderManager
{
	void Init();
	void Render();
}

namespace wand::Renderer
{
	void DrawRect(glm::vec2 pos, glm::vec2 dimens, glm::vec4 color);
}
