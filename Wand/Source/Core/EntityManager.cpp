#include "WandPCH.h"
#include "EntityManager.h"

namespace wand
{
	EntityManager::EntityManager()
	{}

	void EntityManager::Add(UIComponent* component)
	{
		mEntities.push_back(std::unique_ptr<UIComponent>(component));
	}

	std::vector<std::unique_ptr<UIComponent>>& EntityManager::GetEntities() { return mEntities; }
}
