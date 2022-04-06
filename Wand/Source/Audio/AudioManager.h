#pragma once

#include "soloud/soloud.h"
#include "soloud/soloud_wav.h"

namespace wand
{
	class AudioManager
	{
	public:
		AudioManager();
		~AudioManager();

		// Play an audio source and return its handle
		int PlayAudio(SoLoud::Wav& sound, float volume, float panning, float speed) const;
		// Stop playing an audio source
		void StopAudio(int handle) const;
		
	private:
		std::unique_ptr<SoLoud::Soloud> mSoLoud;
	};
}
