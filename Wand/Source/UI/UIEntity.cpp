#include "WandPCH.h"
#include "UIEntity.h"

namespace wand
{
	UIEntity::UIEntity(bool isEnabled)
		: mIsVisible(true), mIsEnabled(isEnabled), mLabel("")
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
	
	// Set a layout so that the entity's position is relative to it
	void UIEntity::SetParentLayout(Transform* layout) { GetDrawable()->SetParentTransform(layout); }

	// Set the x and y coordinates inside the layout
	void UIEntity::SetLayoutPosition(float x, float y)
	{
		if (GetDrawable()->GetParentTransform())
			GetDrawable()->SetParentLayoutCoords(x, y);
	}
	
	// Set the entity's alignment relative to the layout
	void UIEntity::SetLayoutPosition(LayoutPosition horizontal, LayoutPosition vertical)
	{
		if (GetDrawable()->GetParentTransform())
			GetDrawable()->SetParentLayoutPos(horizontal, vertical);
	}
}
