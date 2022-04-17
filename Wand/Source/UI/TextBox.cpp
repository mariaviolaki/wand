#include "WandPCH.h"
#include "TextBox.h"

namespace wand
{
    TextBox::TextBox(const std::string& fontName, unsigned int fontSize, const glm::vec4& color)
        : drawable(std::make_shared<TextGFX>(fontName, fontSize, color)), UIEntity(false)
    {
        SetTransform(drawable->GetTransform());
    }

    Drawable* TextBox::GetDrawable() const { return drawable.get(); }

    void TextBox::SetText(const std::string& newText)
    {
        drawable->Clear();
        drawable->Add(newText);
    }
}
