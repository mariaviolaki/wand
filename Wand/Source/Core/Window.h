#pragma once

#define GLFW_INCLUDE_NONE // to avoid header conflicts with glad
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Events/Event.h"

namespace wand
{
	struct WindowData
	{
		unsigned int width;
		unsigned int height;
		std::function<void(Event*)> EventCallback;
	};

	class Window
	{
	public:
		Window();
		~Window();

		void Init(std::function<void(Event* event)> eventCallback);

		glm::vec2 GetAspectRatio() const;
		float GetStartWidth() const;
		float GetStartHeight() const;
		float GetWidth() const;
		float GetHeight() const;
		std::string GetName() const;

		void SetAspectRatio(unsigned int numer, unsigned int denom);
		void SetStartWidth(unsigned int width);
		void SetStartHeight(unsigned int height);
		void SetWidth(unsigned int width);
		void SetHeight(unsigned int height);
		void SetName(std::string name);

		GLFWwindow* GetGLFWWindow() const;
		bool IsClosed() const;

		void Clear() const;
		void Update() const;

	private:
		GLFWwindow* mWindow;
		std::string mName;
		glm::vec4 mBackgroundColor;
		glm::vec2 mStartDimens;
		glm::vec2 mAspectRatio;
		WindowData mData;

		bool InitGLFW() const;
		bool InitWindow();
		bool InitGLAD() const;
		void SetupWindow() const;
		void SetupCallbacks();
	};
}
