#include "WandPCH.h"
#include "Window.h"

#include "glad/glad.h"

namespace wand
{
	unsigned int Window::sWidth = 0;
	unsigned int Window::sHeight = 0;

	unsigned int Window::GetWidth() { return sWidth; }
	unsigned int Window::GetHeight() { return sHeight; }

	Window::Window(std::string title, int width, int height, glm::vec4 color)
		: mWindow(nullptr), mTitle(title), mColor(color)
	{
		sWidth = width;
		sHeight = height;

		if (!InitGLFW()) return;
		if (!InitWindow()) return;
		if (!InitGLAD()) return;
		SetupWindow();
	}

	Window::~Window()
	{
		if (mWindow)
		{
			glfwDestroyWindow(mWindow);
			glfwTerminate();
		}
	}

	GLFWwindow* Window::GetGLFWWindow() const { return mWindow; }

	bool Window::IsClosed() const {	return glfwWindowShouldClose(mWindow) == 1;	}

	void Window::Update() const
	{
		// Swap front and back window buffers
		glfwSwapBuffers(mWindow);
		// Process new events
		glfwPollEvents();
		// Clear the background with a given color as well as the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
		mWindow = glfwCreateWindow(sWidth, sHeight, mTitle.c_str(), nullptr, nullptr);
		if (!mWindow)
		{
			std::cout << "Failed to create GLFW window.\n";
			glfwTerminate();
			return false;
		}
		// Use this window in the current context
		glfwMakeContextCurrent(mWindow);

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

	void Window::SetupWindow() const
	{
		// Limit the window's frame rate
		glfwSwapInterval(1);
		// Set the background color
		glClearColor(mColor.r, mColor.g, mColor.b, mColor.a);
		// Enable blending and properly rendering transparent pixels
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Render drawables based on their depth (z coord)
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}
}
