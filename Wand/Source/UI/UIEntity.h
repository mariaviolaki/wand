#pragma once

#include "Graphics/Base/Transform.h"
#include "Graphics/Drawable.h"

namespace wand
{
	class UIEntity
	{		
	public:
		virtual Drawable* GetDrawable() const = 0;
		virtual Transform* GetTransform() const = 0;
		bool IsVisible() const;
		virtual void Show();
		virtual void Hide();
		bool IsEnabled() const;
		virtual void Enable();
		virtual void Disable();
		std::string GetLabel() const;
		void SetLabel(const std::string& label);

		std::function<void()> GetLeftClickFunction() const;
		void OnLeftClick(const std::function<void()>& fun);
		void SetParentLayout(Transform* layout);
		void SetLayoutPosition(float x, float y);
		void SetLayoutPosition(LayoutPosition horizontal, LayoutPosition vertical);

	protected:
		UIEntity(bool isEnabled = true);
		bool mIsVisible;
		bool mIsEnabled;

	private:
		std::function<void()> mLeftClickFunction;
		std::string mLabel;
	};
}
