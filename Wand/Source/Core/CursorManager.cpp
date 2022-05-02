#include "WandPCH.h"
#include "CursorManager.h"
#include "stb/stb_image.h"

namespace wand
{
	CursorManager::CursorManager()
		: mArrowCursor(nullptr), mHandCursor(nullptr), mTextInputCursor(nullptr), mWindow(nullptr),
		mCustomArrowCursor(std::make_unique<CustomCursor>()), mCustomHandCursor(std::make_unique<CustomCursor>()),
		mCustomTextInputCursor(std::make_unique<CustomCursor>())
	{}

	CursorManager::~CursorManager()
	{
		DeleteCustomCursorData(mCustomArrowCursor.get());
		DeleteCustomCursorData(mCustomHandCursor.get());
		DeleteCustomCursorData(mCustomTextInputCursor.get());

		glfwDestroyCursor(mArrowCursor);
		glfwDestroyCursor(mHandCursor);
		glfwDestroyCursor(mTextInputCursor);
	}

	void CursorManager::Init(GLFWwindow* window)
	{
		mWindow = window;
		mArrowCursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		mHandCursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
		mTextInputCursor = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
		SetCursor(CursorType::ARROW);
	}

	void CursorManager::SetCursor(CursorType cursorType)
	{
		switch (cursorType)
		{
		case wand::CursorType::ARROW:
			if (mCustomArrowCursor->cursor)
				glfwSetCursor(mWindow, mCustomArrowCursor->cursor);
			else
				glfwSetCursor(mWindow, mArrowCursor);
			break;
		case wand::CursorType::HAND:
			if (mCustomHandCursor->cursor)
				glfwSetCursor(mWindow, mCustomHandCursor->cursor);
			else
				glfwSetCursor(mWindow, mHandCursor);
			break;
		case wand::CursorType::TEXT_INPUT:
			if (mCustomTextInputCursor->cursor)
				glfwSetCursor(mWindow, mCustomTextInputCursor->cursor);
			else
				glfwSetCursor(mWindow, mTextInputCursor);
			break;
		}
	}

	void CursorManager::CreateCursor(CursorType cursorType, std::string imagePath)
	{
		switch (cursorType)
		{
		case CursorType::ARROW:
			SetCustomCursorData(mCustomArrowCursor.get(), imagePath);
			break;
		case CursorType::HAND:
			SetCustomCursorData(mCustomHandCursor.get(), imagePath);
			break;
		case CursorType::TEXT_INPUT:
			SetCustomCursorData(mCustomTextInputCursor.get(), imagePath);
			break;
		}
	}
	
	void CursorManager::SetCustomCursorData(CustomCursor* customCursor, std::string imagePath)
	{
		// Delete any existing data
		DeleteCustomCursorData(customCursor);

		// Flip the image vertically before loading
		stbi_set_flip_vertically_on_load(0);

		// Load the image and fill in its parameters
		int width, height, bytesPerPixel;
		customCursor->image.pixels = stbi_load(imagePath.c_str(), &width, &height, &bytesPerPixel, 4);
		customCursor->image.width = width;
		customCursor->image.height = height;
		customCursor->cursor = glfwCreateCursor(&customCursor->image, 0, 0);
	}

	void CursorManager::DeleteCustomCursorData(CustomCursor* customCursor)
	{
		if (customCursor->image.pixels)
			stbi_image_free(customCursor->image.pixels);
		if (customCursor->cursor)
			glfwDestroyCursor(customCursor->cursor);
	}	
}