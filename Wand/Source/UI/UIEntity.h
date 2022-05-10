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
		/* Visibility methods set if the entity should be rendered or not */
		bool IsVisible() const;
		virtual void Show();
		virtual void Hide();
		/* These methods set if the user can interact with the entity or not */
		bool IsEnabled() const;
		virtual void Enable();
		virtual void Disable();
		/* Use a label to distinguish UI entities */
		std::string GetLabel() const;
		void SetLabel(const std::string& label);
		/* Get/Set functions that run depending on user input */
		std::function<void()> GetLeftClickFunction() const;
		std::function<void()> GetRightClickFunction() const;
		std::function<void()> GetHoverFunction() const;
		void OnLeftClick(const std::function<void()>& fun);
		void OnRightClick(const std::function<void()>& fun);
		void OnHover(const std::function<void()>& fun);
		/* Functions for entities that are children of another entity */
		void SetParentLayout(Transform* layout);
		void SetLayoutPosition(float x, float y);
		void SetLayoutPosition(LayoutPosition horizontal, LayoutPosition vertical);

	protected:
		UIEntity(bool isEnabled = true);
		bool mIsVisible;
		bool mIsEnabled;

	private:
		std::function<void()> mLeftClickFunction;
		std::function<void()> mRightClickFunction;
		std::function<void()> mHoverFunction;
		std::string mLabel;
	};
}
