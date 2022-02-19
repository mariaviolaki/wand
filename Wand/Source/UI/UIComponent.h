#pragma once

namespace wand
{
	class UIComponent
	{
	protected:
		UIComponent(bool isEnabled = false, bool isVisible = false);

	public:
		void IsEnabled(bool isEnabled);
		void IsVisible(bool isVisible);

		bool IsEnabled() const;
		bool IsVisible() const;

	private:
		bool mIsEnabled;
		bool mIsVisible;
	};
}
