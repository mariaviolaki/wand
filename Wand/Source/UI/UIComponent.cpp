#include "WandPCH.h"
#include "UIComponent.h"

namespace wand
{
	UIComponent::UIComponent(bool isEnabled)
		: mIsEnabled(isEnabled)
	{}

	bool UIComponent::IsEnabled() const { return mIsEnabled; }

	void UIComponent::Enable() { mIsEnabled = true; }

	void UIComponent::Disable() { mIsEnabled = false; }
}
