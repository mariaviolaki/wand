#include "WandPCH.h"
#include "UIEntity.h"

namespace wand
{
	UIEntity::UIEntity(bool isEnabled)
		: mIsVisible(false), mIsEnabled(isEnabled), mLabel(""), mLayout(nullptr)
	{}

	bool UIEntity::IsVisible() const { return mIsVisible; }
	void UIEntity::Show() { mIsVisible = true; }
	void UIEntity::Hide() { mIsVisible = false; }

	bool UIEntity::IsEnabled() const { return mIsEnabled; }
	void UIEntity::Enable() { mIsEnabled = true; }
	void UIEntity::Disable() { mIsEnabled = false; }

	std::string UIEntity::GetLabel() const { return mLabel; }
	void UIEntity::SetLabel(const std::string& label) { mLabel = label; }

	std::function<void()> UIEntity::GetLeftClickFunction() const { return mLeftClickFunction; }
	void UIEntity::OnLeftClick(const std::function<void()>& fun) { mLeftClickFunction = fun; }

	Transform& UIEntity::GetTransform() const { return *mTransform.get(); }
	void UIEntity::SetTransform(std::shared_ptr<Transform> transform) { mTransform = transform; }
	
	// Set a layout so that the entity's position is relative to it
	void UIEntity::SetParentLayout(std::shared_ptr<Layout> layout) { mLayout = layout; }

	// Set the x and y coordinates inside the layout
	void UIEntity::SetLayoutPosition(float x, float y)
	{
		if (mLayout == nullptr)
			return;

		glm::vec2 layoutPos = mLayout->GetPosition();
		GetDrawable()->GetTransform()->SetPosition(layoutPos.x + x, layoutPos.y + y);
	}
	
	// Set the entity's alignment relative to the layout
	void UIEntity::SetLayoutPosition(LayoutPosition horizontal, LayoutPosition vertical)
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
}
