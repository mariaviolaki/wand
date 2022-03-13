#include "WandPCH.h"
#include "Text.h"

namespace wand
{
    Text::Text(const std::string& fontName, unsigned int fontSize, const glm::vec4& color)
        : TextGFX(fontName, fontSize, color), UIComponent(GetTransform(), false)
    {}
}
