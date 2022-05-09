#pragma once

namespace wand
{
	class FileManager
	{
	public:
		FileManager();

		std::string GetRootFolder() const;
		// Engine directories
		std::string GetShaderPath() const;
		// Game directories
		std::string GetImagePath() const;
		std::string GetAudioPath() const;
		std::string GetFontPath() const;
		std::string GetSavePath() const;

	private:
		std::string mRootFolder;
		std::string mShaderPath;
		std::string mImagePath;
		std::string mAudioPath;
		std::string mFontPath;
		std::string mSavePath;
	};
}
