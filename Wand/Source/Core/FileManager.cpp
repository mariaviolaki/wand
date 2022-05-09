#include "WandPCH.h"
#include "FileManager.h"

namespace wand
{
	FileManager::FileManager()
		: mRootFolder(SOLUTION_DIR), mShaderPath(""),
		mImagePath(""), mAudioPath(""), mFontPath(""), mSavePath("")
	{
		// Save the directories in the Wand folder
		mShaderPath = mRootFolder + "Wand\\Source\\Graphics\\Base\\Shaders\\";
		// Save the directories in the Game folder
		mImagePath = mRootFolder + "Game\\Images\\";
		mAudioPath = mRootFolder + "Game\\Audio\\";
		mFontPath = mRootFolder + "Game\\Fonts\\";
		mSavePath = mRootFolder + "Game\\Saves\\";

		// Create directories in the default paths if they don't already exist
		std::filesystem::create_directory(mImagePath);
		std::filesystem::create_directory(mAudioPath);
		std::filesystem::create_directory(mFontPath);
		std::filesystem::create_directory(mSavePath);
	}

	std::string FileManager::GetRootFolder() const { return mRootFolder; }
	std::string FileManager::GetShaderPath() const { return mShaderPath; }
	std::string FileManager::GetImagePath() const { return mImagePath; }
	std::string FileManager::GetAudioPath() const { return mAudioPath; }
	std::string FileManager::GetFontPath() const { return mFontPath; }
	std::string FileManager::GetSavePath() const { return mSavePath; }
}
