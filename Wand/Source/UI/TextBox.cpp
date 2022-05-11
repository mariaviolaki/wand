#include "WandPCH.h"
#include "TextBox.h"

namespace wand
{
    TextBox::TextBox(const std::string& fontName, unsigned int fontSize, Color color)
        : mDrawable(std::make_shared<TextGFX>(fontName, fontSize, color)), UIEntity(false)
    {}

    Drawable* TextBox::GetDrawable() const { return mDrawable.get(); }
    Transform* TextBox::GetTransform() const { return mDrawable->GetTransform(); }

    void TextBox::SetText(const std::string& newText)
    {
        mDrawable->Clear();
        mDrawable->Add(newText);
    }

    void TextBox::SetCenteredText(bool isTextCentered)
    {
        mDrawable->SetCenteredText(isTextCentered);
    }
    
    void TextBox::SetFont(std::string fontName, unsigned int fontSize)
    {
        mDrawable->SetFont(fontName, fontSize);
    }
}
