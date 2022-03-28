#include "WandPCH.h"
#include "AudioManager.h"

namespace wand
{
	AudioManager::AudioManager()
		: mSoLoud(std::make_unique<SoLoud::Soloud>())
	{
		// Initialize SoLoud back-end
		mSoLoud->init();
	}

	AudioManager::~AudioManager()
	{
		// Cleanup SoLoud's resources
		mSoLoud->stopAll();
		mSoLoud->deinit();
	}

	int AudioManager::PlayAudio(SoLoud::Wav& sound, float volume, float panning, float speed) const
	{
		// Play the sound
		int handle = mSoLoud->play(sound);
		// Configure the sound
		mSoLoud->setVolume(handle, volume);				// 1.0f is normal
		mSoLoud->setPan(handle, panning);				// -1.0f is left, 1.0f is right
		mSoLoud->setRelativePlaySpeed(handle, speed);	// 1.0f is normal
		return handle;
	}

	void AudioManager::StopAudio(int handle) const
	{
		mSoLoud->stop(handle);
	}
}