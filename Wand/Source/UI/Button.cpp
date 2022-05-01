#include "WandPCH.h"
#include "Button.h"

namespace wand
{
    Button::Button(std::string imagePath, std::string fontName, unsigned int fontSize, glm::vec4 textColor)
        : UIEntity(true), mTextBox(std::make_unique<TextBox>(fontName, fontSize, textColor)),
        mRectangle(nullptr), mSprite(std::make_unique<Sprite>(imagePath))
    {
        mTextBox->GetDrawable()->SetParentTransform(mSprite->GetTransform());
        mTextBox->SetParentLayout(mSprite->GetTransform());
        CenterText();
    }

    Button::Button(glm::vec4 bgColor, std::string fontName, unsigned int fontSize, glm::vec4 textColor)
        : UIEntity(true), mTextBox(std::make_unique<TextBox>(fontName, fontSize, textColor)),
        mRectangle(std::make_unique<Rectangle>(bgColor)), mSprite(nullptr)
    {
        mTextBox->GetDrawable()->SetParentTransform(mRectangle->GetTransform());
        mTextBox->SetParentLayout(mRectangle->GetTransform());
        CenterText();
    }

    Drawable* Button::GetDrawable() const
    {
        if (mRectangle)
            return mRectangle->GetDrawable();
        else
            return mSprite->GetDrawable();
    }

    Drawable* Button::GetTextDrawable() const { return mTextBox->GetDrawable(); }

    Transform* Button::GetTransform() const
    {
        if (mRectangle)
            return mRectangle->GetTransform();
        else
            return mSprite->GetTransform();
    }

    Transform* Button::GetTextTransform() const { return mTextBox->GetTransform(); }

    void Button::SetText(std::string text) { mTextBox->SetText(text); }

    void Button::Show()
    {
        mIsVisible = true;
        mTextBox->Show();
        if (mRectangle)
            mRectangle->Show();
        else
            mSprite->Show();
    }

    void Button::Hide()
    {
        mIsVisible = false;
        mTextBox->Hide();
        if (mRectangle)
            mRectangle->Hide();
        else
            mSprite->Hide();
    }

    void Button::Enable()
    {
        mIsEnabled = true;
        // Only choose the background component to interact with the user
        if (mRectangle)
            mRectangle->Enable();
        else
            mSprite->Enable();
    }

    void Button::Disable()
    {
        mIsEnabled = false;
        // Only choose the background component to interact with the user
        if (mRectangle)
            mRectangle->Disable();
        else
            mSprite->Disable();
    }
    
    void Button::CenterText()
    {
        mTextBox->SetLayoutPosition(LayoutPosition::MIDDLEX, LayoutPosition::MIDDLEY);
        static_cast<TextGFX*>(mTextBox->GetDrawable())->SetCenteredText(true);
    }
}
