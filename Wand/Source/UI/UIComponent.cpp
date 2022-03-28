#include "WandPCH.h"
#include "UIComponent.h"
#include "Input/Input.h"
#include "UIManager.h"

namespace wand
{
	UIComponent::UIComponent(bool isEnabled)
		: mIsEnabled(isEnabled), mIsVisible(false), mLayout(nullptr)
	{}

	bool UIComponent::IsVisible() const { return mIsVisible; }

	void UIComponent::Show() { mIsVisible = true; }

	void UIComponent::Hide() { mIsVisible = false; }

	void UIComponent::SetTransform(std::shared_ptr<Transform> transform) { mTransform = transform; }

	bool UIComponent::IsEnabled() const { return mIsEnabled; }

	void UIComponent::Enable() { mIsEnabled = true; }

	void UIComponent::Disable() { mIsEnabled = false; }

	Transform& UIComponent::GetTransform() const { return *mTransform.get(); }

	std::function<void()> UIComponent::GetFunction() const { return mFunction; }
	
	// Set a layout so that the component's position is relative to it
	void UIComponent::SetParentLayout(std::shared_ptr<Layout> layout) { mLayout = layout; }

	// Set the x and y coordinates inside the layout
	void UIComponent::SetLayoutPosition(float x, float y)
	{
		if (mLayout == nullptr)
			return;

		glm::vec2 layoutPos = mLayout->GetPosition();
		GetDrawable()->GetTransform()->SetPosition(layoutPos.x + x, layoutPos.y + y);
	}
	
	// Set the component's alignment relative to the layout
	void UIComponent::SetLayoutPosition(LayoutPosition horizontal, LayoutPosition vertical)
	{
		if (mLayout == nullptr)
			return;

		float x, y;
		glm::vec2 layoutPos = mLayout->GetPosition();
		auto transform = GetDrawable()->GetTransform();

		// Set position on the x axis
		if (horizontal == LayoutPosition::LEFT)
			x = layoutPos.x;
		else if (horizontal == LayoutPosition::RIGHT)
			x = layoutPos.x + mLayout->GetWidth() - transform->GetWidth();
		else // align at center
			x = layoutPos.x + (mLayout->GetWidth() / 2) - (transform->GetWidth() / 2);

		// Set position on the y axis
		if (vertical == LayoutPosition::BOTTOM)
			y = layoutPos.y;
		else if (vertical == LayoutPosition::TOP)
			y = layoutPos.y + mLayout->GetHeight() - transform->GetHeight();
		else // align at center
			y = layoutPos.y + (mLayout->GetHeight() / 2) - (transform->GetHeight() / 2);

		transform->SetPosition(x, y);
	}

	void UIComponent::OnClick(const std::function<void()>& fun)
	{
		if (mIsEnabled)
		{
			auto transform = GetDrawable()->GetTransform();
			glm::vec2 pos = transform->GetPosition();
			// Call function if the user clicked inside the borders
			if (Input::IsMouseInArea(pos.x, pos.y, transform->GetWidth(), transform->GetHeight())
				&& Input::GetMouseButtonStatus(MOUSE_BUTTON_LEFT) == ButtonStatus::PRESSED)
			{
				mFunction = fun;
				UIManager::Add(this);
			}
		}
	}
}
