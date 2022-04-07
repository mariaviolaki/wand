#include "WandPCH.h"
#include "AudioSource.h"

namespace wand
{
	AudioSource::AudioSource(const std::string& filepath, bool isLooping)
		: mAudio(std::make_unique<SoLoud::Wav>()), mHandle(-1), mIsLooping(isLooping)
	{
		// Load a wav/flac/mp3/ogg file
		mAudio->load(filepath.c_str());
		mAudio->setLooping(isLooping);
	}

	SoLoud::Wav& AudioSource::GetAudio() const { return *mAudio.get(); }

	bool AudioSource::GetLooping() const { return mIsLooping; }
	void AudioSource::SetLooping(bool isLooping) { mIsLooping = isLooping; }

	int AudioSource::GetHandle() const { return mHandle; }
	void AudioSource::SetHandle(int handle) { mHandle = handle; }
}
