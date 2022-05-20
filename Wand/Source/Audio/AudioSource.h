#pragma once

#include "soloud/soloud_wav.h"

namespace wand
{
	class AudioSource
	{
	public:
		AudioSource(const std::string& filepath, bool looping = false);
		SoLoud::Wav& GetAudio() const;
		bool IsLooping() const;
		void SetLooping(bool isLooping);
		int GetHandle() const;
		void SetHandle(int handle);

	private:
		std::unique_ptr<SoLoud::Wav> mAudio;
		bool mIsLooping;
		int mHandle;
	};
}
