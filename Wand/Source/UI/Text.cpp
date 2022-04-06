#include "WandPCH.h"
#include "Text.h"

namespace wand
{
    Text::Text(const std::string& fontName, unsigned int fontSize, const glm::vec4& color)
        : drawable(std::make_shared<TextGFX>(fontName, fontSize, color)), UIEntity(false)
    {
        SetTransform(drawable->GetTransform());
    }

    Drawable* Text::GetDrawable() const { return drawable.get(); }

    void Text::Add(const std::string& newText) { drawable->Add(newText); }
}
