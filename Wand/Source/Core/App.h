#pragma once

#include "Window.h"

namespace wand
{
	class App
	{
	public:
		App();
		~App();

		bool IsRunning() const;
		void Update() const;
		
	private:
		std::unique_ptr<Window> mWindow;

		void Start();
	};
}
