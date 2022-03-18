#pragma once

#include "Window.h"
#include "EntityManager.h"
#include "Graphics/Renderer.h"
#include "UI/UIComponent.h"

namespace wand
{
	class App
	{
	public:
		App();
		~App();

		void Update() const;
		bool IsRunning() const;

		UIComponent& AddEntity(UIComponent* entity);
		
	private:
		std::unique_ptr<Window> mWindow;
		std::unique_ptr<EntityManager> mEntityManager;
		std::unique_ptr<Renderer> mRenderer;

		void Start();
	};
}
