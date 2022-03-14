#include "WandPCH.h"
#include "UIComponent.h"
#include "Input/Input.h"
#include "UIManager.h"

namespace wand
{
	UIComponent::UIComponent(std::shared_ptr<Transform> transform, bool isEnabled)
		: mTransform(transform), mLayout(nullptr), mIsEnabled(isEnabled)
	{}

	bool UIComponent::IsEnabled() const { return mIsEnabled; }

	void UIComponent::Enable() { mIsEnabled = true; }

	void UIComponent::Disable() { mIsEnabled = false; }

	void UIComponent::OnClick(const std::function<void()>& fun)
	{
		if (mIsEnabled)
		{
			glm::vec2 pos = mTransform->GetPosition();
			// Call function if the user clicked inside the borders
			if (Input::IsMouseInArea(pos.x, pos.y, mTransform->GetWidth(), mTransform->GetHeight())
				&& Input::GetMouseButtonStatus(MOUSE_BUTTON_LEFT) == ButtonStatus::PRESSED)
			{
				mFunction = fun;
				UIManager::Add(this);
			}
		}
	}

	const Transform& UIComponent::GetUITransform() const { return *mTransform.get(); }

	std::function<void()> UIComponent::GetFunction() const { return mFunction; }
	
	// Set a layout so that the component's position is relative to it
	void UIComponent::SetParentLayout(std::shared_ptr<Layout> layout)
	{
		mLayout = layout;
	}

	// Set the x and y coordinates inside the layout
	void UIComponent::SetLayoutPosition(float x, float y)
	{
		if (mLayout == nullptr)
			return;

		glm::vec2 layoutPos = mLayout->GetPosition();
		mTransform->SetPosition(layoutPos.x + x, layoutPos.y + y);
	}
	
	// Set the component's alignment relative to the layout
	void UIComponent::SetLayoutPosition(LayoutPosition horizontal, LayoutPosition vertical)
	{
		if (mLayout == nullptr)
			return;

		float x, y;
		glm::vec2 layoutPos = mLayout->GetPosition();

		// Set position on the x axis
		if (horizontal == LayoutPosition::LEFT)
			x = layoutPos.x;
		else if (horizontal == LayoutPosition::RIGHT)
			x = layoutPos.x + mLayout->GetWidth() - mTransform->GetWidth();
		else // align at center
			x = layoutPos.x + (mLayout->GetWidth() / 2) - (mTransform->GetWidth() / 2);

		// Set position on the y axis
		if (vertical == LayoutPosition::BOTTOM)
			y = layoutPos.y;
		else if (vertical == LayoutPosition::TOP)
			y = layoutPos.y + mLayout->GetHeight() - mTransform->GetHeight();
		else // align at center
			y = layoutPos.y + (mLayout->GetHeight() / 2) - (mTransform->GetHeight() / 2);

		mTransform->SetPosition(x, y);
	}
}
