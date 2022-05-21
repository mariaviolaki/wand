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
		Window(std::string name, unsigned int width, unsigned int height);
		~Window();

		void Init(std::function<void(Event* event)> eventCallback, std::function<void()> updateCallback);

		glm::vec2 GetAspectRatio() const;
		float GetStartWidth() const;
		float GetStartHeight() const;
		float GetWidth() const;
		float GetHeight() const;
		std::string GetName() const;
		bool IsFullscreen() const;

		void SetAspectRatio(unsigned int numer, unsigned int denom);
		void SetWidth(unsigned int width);
		void SetHeight(unsigned int height);
		void SetName(std::string name);
		void SetFullscreen(bool fullscreen);
		void SetIcon(std::string imagePath);

		GLFWwindow* GetGLFWWindow() const;
		bool IsClosed() const;
		// Save a function that will run before the app exits
		void OnClose(std::function<void()> closeFunction);
		// Run all the OnClose functions before exiting
		void RunCloseFunctions();

		void Clear() const;
		void Update() const;
		void Close() const;

	private:
		GLFWwindow* mWindow;
		std::string mName;
		glm::vec4 mBackgroundColor;
		glm::vec2 mStartDimens;
		glm::vec2 mAspectRatio;
		glm::ivec2 mPosition;
		WindowData mData;
		bool mIsFullscreen;
		GLFWimage mIcons[1];
		std::vector<std::function<void()>> mCloseFunctions;
		std::function<void()> mUpdateCallback;

		bool InitGLFW() const;
		bool InitWindow();
		bool InitGLAD() const;
		void SetupWindow();
		void SetupCallbacks();
	};
}
