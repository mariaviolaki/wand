#include "WandPCH.h"
#include "Window.h"
#include "glad/glad.h"

namespace wand
{
	unsigned int Window::sWidth = 0;
	unsigned int Window::sHeight = 0;

	unsigned int Window::GetWidth() { return sWidth; }
	unsigned int Window::GetHeight() { return sHeight; }

	Window::Window()
		: mWindow(nullptr), mData()
	{}

	Window::~Window()
	{
		if (mWindow)
		{
			glfwDestroyWindow(mWindow);
			glfwTerminate();
		}
	}

	void Window::Init(WindowData windowData)
	{
		mData = windowData;
		sWidth = windowData.width;
		sHeight = windowData.height;

		if (!InitGLFW()) return;
		if (!InitWindow()) return;
		if (!InitGLAD()) return;
		SetupWindow();
	}

	GLFWwindow* Window::GetGLFWWindow() const { return mWindow; }

	bool Window::IsClosed() const {	return glfwWindowShouldClose(mWindow) == 1;	}

	void Window::Update() const
	{
		// Swap front and back window buffers
		glfwSwapBuffers(mWindow);
		// Clear the background with a given color as well as the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Process new events
		glfwPollEvents();
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
		mWindow = glfwCreateWindow(sWidth, sHeight, mData.title.c_str(), nullptr, nullptr);
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
		glClearColor(mData.color.r, mData.color.g, mData.color.b, mData.color.a);
		// Enable blending and properly rendering transparent pixels
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Associate the window data with the GLFW window
		glfwSetWindowUserPointer(mWindow, (void*)&mData);
	}
}
