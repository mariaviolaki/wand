#include "Window.h"

#include <iostream>

namespace wand
{
	Window::Window(std::string title, int width, int height)
		: mWindow(nullptr), mTitle(title), mWidth(width), mHeight(height)
	{
		// Initialize GLFW to use its functions
		if (!glfwInit())
		{
			std::cout << "Could not initialize GLFW.\n";
			return;
		}
		Init();
	}

	void Window::Init()
	{			
		// Create a new window with GLFW
		mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);
		if (!mWindow)
		{
			std::cout << "Could not create GLFW window.\n";
			glfwTerminate();
			return;
		}
		// Use this window in the current context
		glfwMakeContextCurrent(mWindow);
	}

	void Window::Update() const
	{
		// Swap front and back window buffers
		glfwSwapBuffers(mWindow);
		// Process new events
		glfwPollEvents();
	}

	bool Window::IsClosed() const
	{
		return glfwWindowShouldClose(mWindow) == 1;
	}

	Window::~Window()
	{
		if (mWindow)
		{
			glfwDestroyWindow(mWindow);
			glfwTerminate();
		}
	}
}
