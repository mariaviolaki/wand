#pragma once

#include "AudioManager.h"
#include "soloud/soloud_wav.h"

namespace wand
{
	class AudioSource
	{
	public:
		AudioSource(AudioManager* audioManager, const std::string& filepath, bool looping = true);
		void Play(float volume = 1.0f, float panning = 0.0f, float speed = 1.0f);
		void Stop();

	private:
		std::shared_ptr<SoLoud::Wav> mSound;
		AudioManager* mAudioManager;
		int mHandle;
	};
}
