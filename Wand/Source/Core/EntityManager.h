#pragma once

#include "UI/UIEntity.h"

namespace wand
{
	class EntityManager
	{
	public:
		EntityManager();

		void Add(UIEntity* entity);
		std::vector<std::unique_ptr<UIEntity>>& GetEntities();

	private:
		std::vector<std::unique_ptr<UIEntity>> mEntities;
	};
}
