#pragma once

#define GLFW_INCLUDE_NONE // to avoid header conflicts with glad
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Events/Event.h"

namespace wand
{
	struct WindowData
	{
		std::string title;
		int width;
		int height;
		glm::vec4 color;
		std::function<void(Event*)> EventCallback;
	};

	class Window
	{
	public:
		static unsigned int GetWidth();
		static unsigned int GetHeight();

		Window();
		~Window();

		void Init(WindowData windowData);
		GLFWwindow* GetGLFWWindow() const;
		bool IsClosed() const;
		void Update() const;

	private:
		static unsigned int sWidth;
		static unsigned int sHeight;

		GLFWwindow* mWindow;
		WindowData mData;

		bool InitGLFW() const;
		bool InitWindow();
		bool InitGLAD() const;
		void SetupWindow() const;
	};
}
