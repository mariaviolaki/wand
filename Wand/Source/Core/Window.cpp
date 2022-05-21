#include "WandPCH.h"
#include "Window.h"
#include "glad/glad.h"
#include "stb/stb_image.h"
#include "Utils/Logger.h"

namespace wand
{
	Window::Window(std::string name, unsigned int width, unsigned int height)
		: mWindow(nullptr), mName(name), mBackgroundColor({ 0.1f, 0.1f, 0.1f, 1.0f }),
		mStartDimens({ width, height }), mAspectRatio({ 16.0f, 9.0f }), mData({ width, height, nullptr }),
		mIsFullscreen(false), mPosition({ 0, 0 }), mIcons()
	{}

	Window::~Window()
	{
		if (mWindow)
		{
			glfwDestroyWindow(mWindow);
			glfwTerminate();
		}
		if (mIcons[0].pixels)
			stbi_image_free(mIcons[0].pixels);
	}

	void Window::Init(std::function<void(Event* event)> eventCallback, std::function<void()> updateCallback)
	{
		mData.EventCallback = eventCallback;
		mUpdateCallback = updateCallback;

		if (!InitGLFW()) return;
		if (!InitWindow()) return;
		if (!InitGLAD()) return;
		SetupWindow();
		SetupCallbacks();
	}

	glm::vec2 Window::GetAspectRatio() const { return mAspectRatio; }
	float Window::GetStartWidth() const { return mStartDimens.x; }
	float Window::GetStartHeight() const { return mStartDimens.y; }
	float Window::GetWidth() const { return mData.width; }
	float Window::GetHeight() const { return mData.height; }
	std::string Window::GetName() const { return mName; }
	bool Window::IsFullscreen() const { return mIsFullscreen; }

	void Window::SetAspectRatio(unsigned int numer, unsigned int denom)
	{
		// Update the entities in the app before resizing
		mUpdateCallback();
		mAspectRatio = glm::vec2(numer, denom);
		WindowResizeEvent* event = new WindowResizeEvent(mData.width, mData.height);
		mData.EventCallback(event);
	}
	void Window::SetWidth(unsigned int width) { mData.width = width; }
	void Window::SetHeight(unsigned int height) { mData.height = height; }
	void Window::SetName(std::string name)
	{
		mName = name;
		glfwSetWindowTitle(mWindow, name.c_str());
	}

	void Window::SetFullscreen(bool fullscreen)
	{
		if (fullscreen)
		{
			if (mIsFullscreen)
				return;
			// Save the current position of the window
			glfwGetWindowPos(mWindow, &mPosition.x, &mPosition.y);
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(mWindow, monitor,
				0, 0, mode->width, mode->height, mode->refreshRate);
		}
		else
		{
			if (!mIsFullscreen)
				return;
			glfwSetWindowMonitor(mWindow, nullptr,
				mPosition.x, mPosition.y, mStartDimens.x, mStartDimens.y, GLFW_DONT_CARE);
		}
		mIsFullscreen = fullscreen;
	}

	void Window::SetIcon(std::string imagePath)
	{
		// Free any previously loaded icons
		if (mIcons[0].pixels)
			stbi_image_free(mIcons[0].pixels);
		// Flip the image vertically before loading
		stbi_set_flip_vertically_on_load(0);
		mIcons[0].pixels = stbi_load(imagePath.c_str(), &mIcons[0].width, &mIcons[0].height, 0, 4);
		glfwSetWindowIcon(mWindow, 1, mIcons);
	}

	GLFWwindow* Window::GetGLFWWindow() const { return mWindow; }
	bool Window::IsClosed() const { return glfwWindowShouldClose(mWindow) == 1; }

	void Window::OnClose(std::function<void()> closeFunction)
	{
		mCloseFunctions.emplace_back(closeFunction);
	}

	void Window::RunCloseFunctions()
	{
		for (auto& closeFunction : mCloseFunctions)
			closeFunction();
	}

	void Window::Clear() const
	{
		// Clear the background with a given color as well as the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Process new events
		glfwPollEvents();
	}

	void Window::Update() const
	{
		// Swap front and back window buffers
		glfwSwapBuffers(mWindow);
	}

	void Window::Close() const
	{
		glfwSetWindowShouldClose(mWindow, GL_TRUE);
	}

	// Initialize GLFW to use its functions
	bool Window::InitGLFW() const
	{
		if (glfwInit())
			return true;

		Logger::EngineLog("Window", "Failed to initialize GLFW.\n");
		return false;
	}

	bool Window::InitWindow()
	{
		// Create a new window with GLFW
		mWindow = glfwCreateWindow(mData.width, mData.height, mName.c_str(), nullptr, nullptr);
		if (!mWindow)
		{
			Logger::EngineLog("Window", "Failed to create GLFW window.\n");
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

		Logger::EngineLog("Window", "Failed to load the OpenGL functions.\n");
		return false;
	}

	void Window::SetupWindow()
	{
		// Limit the window's frame rate
		glfwSwapInterval(1);
		// Set the background color
		glClearColor(mBackgroundColor.r, mBackgroundColor.g, mBackgroundColor.b, mBackgroundColor.a);
		// Enable blending and properly rendering transparent pixels
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Associate the window data with the GLFW window
		glfwSetWindowUserPointer(mWindow, (void*)&mData);
		// Save the current position of the window
		glfwGetWindowPos(mWindow, &mPosition.x, &mPosition.y);
	}

	void Window::SetupCallbacks()
	{
		glfwSetFramebufferSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
			{
				WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
				WindowResizeEvent* event = new WindowResizeEvent((unsigned int)width, (unsigned int)height);
				data->EventCallback(event);
			});

		glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window)
			{
				WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent* event = new WindowCloseEvent();
				data->EventCallback(event);
			});
	}
}
