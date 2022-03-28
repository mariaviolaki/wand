#pragma once

#include "Graphics/Base/Transform.h"
#include "Layout.h"
#include "Graphics/Drawable.h"

namespace wand
{
	class UIComponent
	{
	protected:
		UIComponent(bool isEnabled = true);
		void SetTransform(std::shared_ptr<Transform> transform);
		
	public:
		virtual Drawable* GetDrawable() const = 0;
		bool IsVisible() const;
		void Show();
		void Hide();
		bool IsEnabled() const;
		void Enable();
		void Disable();

		Transform& GetTransform() const;
		std::function<void()> GetFunction() const;
		void SetParentLayout(std::shared_ptr<Layout> layout);
		void SetLayoutPosition(float x, float y);
		void SetLayoutPosition(LayoutPosition horizontal, LayoutPosition vertical);
		void OnClick(const std::function<void()>& fun);

	private:
		std::shared_ptr<Transform> mTransform;
		std::shared_ptr<Layout> mLayout;
		std::function<void()> mFunction;
		bool mIsVisible;
		bool mIsEnabled;
	};
}
