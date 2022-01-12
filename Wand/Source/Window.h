#pragma once

#include <string>
#define GLFW_INCLUDE_NONE // to avoid header conflicts with glad
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

		bool InitGLFW() const;
		bool InitWindow();
		bool InitGLAD() const;
	};
}
