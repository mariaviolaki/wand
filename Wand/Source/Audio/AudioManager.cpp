#include "WandPCH.h"
#include "AudioManager.h"
#include "SoLoud/soloud_thread.h"

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
		// Start the sound in paused state
		int handle = mSoLoud->play(sound, volume, panning, true);
		// Configure the sound
		mSoLoud->setRelativePlaySpeed(handle, speed);
		// Unpause the sound
		mSoLoud->setPause(handle, 0);
		// Wait until the sound is finished
		SoLoud::Thread::sleep(100);
		return handle;
	}

	void AudioManager::StopAudio(int handle) const
	{
		mSoLoud->stop(handle);
	}
}
