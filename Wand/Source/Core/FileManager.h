#pragma once

namespace wand
{
	class FileManager
	{
	public:
		FileManager();

		std::string GetImagePath() const;
		std::string GetAudioPath() const;
		std::string GetFontPath() const;
		std::string GetSavePath() const;

	private:
		std::string mImagePath;
		std::string mAudioPath;
		std::string mFontPath;
		std::string mSavePath;
	};
}
