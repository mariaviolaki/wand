#pragma once

#include "Graphics/Base/Transform.h"
#include "Layout.h"

namespace wand
{
	class UIComponent
	{
	protected:
		UIComponent(std::shared_ptr<Transform> transform, bool isEnabled = true);
		
	public:
		bool IsEnabled() const;
		void Enable();
		void Disable();
		void OnClick(const std::function<void()>& fun);
		const Transform& GetUITransform() const;
		std::function<void()> GetFunction() const;
		void SetParentLayout(std::shared_ptr<Layout> layout);
		void SetLayoutPosition(float x, float y);
		void SetLayoutPosition(LayoutPosition horizontal, LayoutPosition vertical);

	private:
		std::shared_ptr<Transform> mTransform;
		std::shared_ptr<Layout> mLayout;
		std::function<void()> mFunction;
		bool mIsEnabled;
	};
}
