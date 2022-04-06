#include "WandPCH.h"
#include "AudioSource.h"

namespace wand
{
	AudioSource::AudioSource(AudioManager* audioManager, const std::string& filepath, bool looping)
		: mSound(std::make_shared<SoLoud::Wav>()), mAudioManager(audioManager), mHandle(0)
	{
		// Load a wav/flac/mp3/ogg file
		mSound->load(filepath.c_str());
		mSound->setLooping(looping);
	}

	void AudioSource::Play(float volume, float panning, float speed)
	{
		if (!this) return; // don's play a non-existing audio source
		mHandle = mAudioManager->PlayAudio(*mSound.get(), volume, panning, speed);
	}

	void AudioSource::Stop()
	{
		if (!this) return; // don's stop playing a non-existing audio source
		mAudioManager->StopAudio(mHandle);
	}
}
