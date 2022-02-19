#include "WandPCH.h"
#include "UIComponent.h"

namespace wand
{
	UIComponent::UIComponent(bool isEnabled, bool isVisible)
		: mIsEnabled(isEnabled), mIsVisible(isVisible)
	{}

	void UIComponent::IsEnabled(bool isEnabled) { mIsEnabled = isEnabled; }

	void UIComponent::IsVisible(bool isVisible) { mIsVisible = isVisible; }

	bool UIComponent::IsEnabled() const { return mIsEnabled; }

	bool UIComponent::IsVisible() const { return mIsVisible; }
}
