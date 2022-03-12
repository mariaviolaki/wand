#pragma once

namespace wand
{
	class UIComponent
	{
	protected:
		UIComponent(bool isEnabled = false);
		
	public:
		bool IsEnabled() const;
		void Enable();
		void Disable();
		virtual void OnClick(const std::function<void()>& fun) = 0;

	private:
		bool mIsEnabled;
	};
}
