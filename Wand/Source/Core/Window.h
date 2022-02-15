#pragma once

#define GLFW_INCLUDE_NONE // to avoid header conflicts with glad
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

namespace wand
{
	class Window
	{
	public:
		static unsigned int GetWidth();
		static unsigned int GetHeight();

		// Constructor for a window with the default settings
		Window(std::string title = "Wand Engine", 
			int width = 960, int height = 540, 
			glm::vec4 color = {0.1f, 0.1f, 0.1f, 0.1f});
		~Window();

		GLFWwindow* GetGLFWWindow() const;
		bool IsClosed() const;

		void Update() const;

	private:
		static unsigned int sWidth;
		static unsigned int sHeight;

		GLFWwindow* mWindow;
		std::string mTitle;
		glm::vec4 mColor;

		bool InitGLFW() const;
		bool InitWindow();
		bool InitGLAD() const;
		void SetupWindow() const;
	};
}
