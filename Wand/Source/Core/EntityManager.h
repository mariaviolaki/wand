#pragma once

#include "UI/Rectangle.h"
#include "UI/Sprite.h"
#include "UI/Text.h"

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
