#include "WandPCH.h"
#include "TextBox.h"

namespace wand
{
    TextBox::TextBox(const std::string& fontName, unsigned int fontSize, Color color)
        : drawable(std::make_shared<TextGFX>(fontName, fontSize, color)), UIEntity(false)
    {}

    Drawable* TextBox::GetDrawable() const { return drawable.get(); }
    Transform* TextBox::GetTransform() const { return drawable->GetTransform(); }

    void TextBox::SetText(const std::string& newText)
    {
        drawable->Clear();
        drawable->Add(newText);
    }
}
