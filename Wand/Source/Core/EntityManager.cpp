#include "WandPCH.h"
#include "EntityManager.h"

namespace wand
{
	EntityManager::EntityManager()
	{}

	void EntityManager::Add(UIEntity* entity)
	{
		mEntities.push_back(std::unique_ptr<UIEntity>(entity));
	}

	std::vector<std::unique_ptr<UIEntity>>& EntityManager::GetEntities() { return mEntities; }
}
