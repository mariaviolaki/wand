#include "Window.h"

#include <iostream>
#include "glad/glad.h"
#include "Input/Input.h"

namespace wand
{
	Window::Window(std::string title, int width, int height)
		: mWindow(nullptr), mTitle(title), mWidth(width), mHeight(height)
	{
		if (!InitGLFW()) return;
		if (!InitWindow()) return;
		if (!InitGLAD()) return;
		InputManager::SetupCallbacks(mWindow);
	}

	// Initialize GLFW to use its functions
	bool Window::InitGLFW() const
	{
		if (glfwInit())
			return true;

		std::cout << "Failed to initialize GLFW.\n";
		return false;	
	}

	bool Window::InitWindow()
	{			
		// Create a new window with GLFW
		mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);
		if (!mWindow)
		{
			std::cout << "Failed to create GLFW window.\n";
			glfwTerminate();
			return false;
		}
		// Use this window in the current context
		glfwMakeContextCurrent(mWindow);
		// Limit the window's frame rate
		glfwSwapInterval(1);

		return true;
	}

	// Load the OpenGL functions with glad after creating a valid OpenGL context (window)
	bool Window::InitGLAD() const
	{
		if (gladLoadGL())
			return true;
		
		std::cout << "Failed to load the OpenGL functions.\n";
		return false;
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
