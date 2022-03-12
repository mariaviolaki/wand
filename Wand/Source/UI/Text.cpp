#include "WandPCH.h"
#include "Text.h"
#include "Input/Input.h"

namespace wand
{
    Text::Text(const std::string& fontName, unsigned int fontSize, const glm::vec4& color)
        : TextGFX(fontName, fontSize, color)
    {}

    void Text::OnClick(const std::function<void()>&fun)
    {
        glm::vec3 pos = GetPosition();
        if (Input::IsMouseInArea(pos.x, pos.y, GetWidth(), GetHeight())
            && Input::GetMouseButtonStatus(MOUSE_BUTTON_LEFT) == ButtonStatus::PRESSED)
        {
            fun();
        }
    }
}
