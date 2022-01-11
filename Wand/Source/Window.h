#pragma once

#include <string>
#include "GLFW/glfw3.h"

namespace wand
{
	class Window
	{
	public:
		Window(std::string title = "Wand Engine", int width = 960, int height = 540);
		~Window();

		void Update() const;
		bool IsClosed() const;

	private:
		GLFWwindow* mWindow;
		std::string mTitle;
		int mWidth;
		int mHeight;

		void Init();
	};
}
