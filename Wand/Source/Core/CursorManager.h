#pragma once

#include "GLFW/glfw3.h"

namespace wand
{
	enum class CursorType
	{
		ARROW, HAND, TEXT_INPUT
	};

	struct CustomCursor
	{
		GLFWimage image;
		GLFWcursor* cursor;
	};

	class CursorManager
	{
	public:
		CursorManager();
		~CursorManager();

		void Init(GLFWwindow* window);
		// Set the cursor type to arrow, hand, or text input
		void SetCursor(CursorType cursorType);
		// Create a custom cursor from an image file
		void CreateCursor(CursorType cursorType, std::string imagePath);
		
	private:
		GLFWcursor* mArrowCursor;
		GLFWcursor* mHandCursor;
		GLFWcursor* mTextInputCursor;
		GLFWwindow* mWindow;
		std::unique_ptr<CustomCursor> mCustomArrowCursor;
		std::unique_ptr<CustomCursor> mCustomHandCursor;
		std::unique_ptr<CustomCursor> mCustomTextInputCursor;

		void SetCustomCursorData(CustomCursor* customCursor, std::string imagePath);
		void DeleteCustomCursorData(CustomCursor* customCursor);
	};
}
