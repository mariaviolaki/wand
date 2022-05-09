#include "WandPCH.h"
#include "AudioManager.h"
#include "soloud/soloud_wav.h"
#include "Utils/Logger.h"

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
		mAudioSources.clear();
		// Cleanup SoLoud's resources
		mSoLoud->stopAll();
		mSoLoud->deinit();
	}

	void AudioManager::Add(std::string filepath, std::string name)
	{
		// If the audio file exists, add an audio source to the map
		if (std::filesystem::exists(filepath))
			mAudioSources.emplace(std::make_pair(name, std::unique_ptr<AudioSource>(new AudioSource(filepath))));
		else
			Logger::EngineLog("AudioManager", "Audio file not found in location: " + filepath + "\n");
	}

	void AudioManager::Play(const std::string& name, float volume, float panning, float speed)
	{
		// Get the correct audio source from the map
		AudioSource* audioSource = mAudioSources[name].get();
		if (!audioSource)
			return;

		// Start the sound in paused state
		int handle = mSoLoud->play(audioSource->GetAudio(), volume, panning, true);
		// Configure the sound
		mSoLoud->setRelativePlaySpeed(handle, speed);
		// Unpause the sound
		mSoLoud->setPause(handle, 0);
		// Save the handle to stop the playback later
		audioSource->SetHandle(handle);
	}

	void AudioManager::Stop(const std::string& name)
	{
		// Get the correct audio source from the map
		AudioSource* audioSource = mAudioSources[name].get();
		if (!audioSource || audioSource->GetHandle() == -1)
			return;

		// Stop the playback using the saved handle
		mSoLoud->stop(audioSource->GetHandle());
		// Reset the handle
		audioSource->SetHandle(-1);
	}
}
