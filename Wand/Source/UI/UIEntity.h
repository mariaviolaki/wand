#pragma once

#include "Graphics/Base/Transform.h"
#include "Layout.h"
#include "Graphics/Drawable.h"

namespace wand
{
	class UIEntity
	{
	protected:
		UIEntity(bool isEnabled = true);
		void SetTransform(std::shared_ptr<Transform> transform);
		
	public:
		virtual Drawable* GetDrawable() const = 0;
		bool IsVisible() const;
		void Show();
		void Hide();
		bool IsEnabled() const;
		void Enable();
		void Disable();
		std::string GetLabel() const;
		void SetLabel(const std::string& label);

		std::function<void()> GetLeftClickFunction() const;
		void OnLeftClick(const std::function<void()>& fun);
		Transform& GetTransform() const;
		void SetParentLayout(std::shared_ptr<Layout> layout);
		void SetLayoutPosition(float x, float y);
		void SetLayoutPosition(LayoutPosition horizontal, LayoutPosition vertical);

	private:
		std::shared_ptr<Transform> mTransform;
		std::shared_ptr<Layout> mLayout;
		std::function<void()> mLeftClickFunction;
		std::string mLabel;
		bool mIsVisible;
		bool mIsEnabled;
	};
}
