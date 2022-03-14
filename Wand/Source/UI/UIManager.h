#pragma once

#include "UIComponent.h"

namespace wand
{
	class UIManager
	{
	public:
		static void Add(UIComponent* component);
		static void ProcessClickFunction();
	private:
		static std::vector<UIComponent*> components;
	};
}