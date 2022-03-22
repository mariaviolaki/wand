#pragma once

#include "UI/UIComponent.h"

namespace wand
{
	class EntityManager
	{
	public:
		EntityManager();

		void Add(UIComponent* component);
		std::vector<std::unique_ptr<UIComponent>>& GetEntities();

	private:
		std::vector<std::unique_ptr<UIComponent>> mEntities;
	};
}
