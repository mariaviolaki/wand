#pragma once

#include "AudioSource.h"
#include "soloud/soloud.h"

namespace wand
{
	class AudioManager
	{
	public:
		AudioManager();
		~AudioManager();

		// Add an audio file to the map
		void Add(std::string filepath, std::string name, bool looping);
		// Play an audio file from the map
		void Play(const std::string& name, float volume = 1.0f, float panning = 0.0f, float speed = 1.0f);
		// Stop an audio file from the map
		void Stop(const std::string& name);

	private:
		std::unique_ptr<SoLoud::Soloud> mSoLoud;
		std::unordered_map<std::string, std::unique_ptr<AudioSource>> mAudioSources;
	};
}
