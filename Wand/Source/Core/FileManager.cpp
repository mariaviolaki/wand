#include "WandPCH.h"
#include "FileManager.h"

namespace wand
{
	FileManager::FileManager()
		: mImagePath(std::filesystem::current_path().string() + "/Images/"),
		mAudioPath(std::filesystem::current_path().string() + "/Audio/"),
		mFontPath(std::filesystem::current_path().string() + "/Fonts/"),
		mSavePath(std::filesystem::current_path().string() + "/Saves/")
	{
		// Create directories in the default paths if they don't already exist
		std::filesystem::create_directory(mImagePath);
		std::filesystem::create_directory(mAudioPath);
		std::filesystem::create_directory(mFontPath);
		std::filesystem::create_directory(mSavePath);
	}

	std::string FileManager::GetImagePath() const { return mImagePath; }
	std::string FileManager::GetAudioPath() const { return mAudioPath; }
	std::string FileManager::GetFontPath() const { return mFontPath; }
	std::string FileManager::GetSavePath() const { return mSavePath; }
}
