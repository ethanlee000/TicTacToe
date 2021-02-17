#pragma once

#include <SFML/Audio.hpp>

namespace hgw
{
	class MusicManager
	{
	public:
		MusicManager() {};
		~MusicManager() {};

		sf::Music gameMusic;

		void LoopPlay(sf::Music &music, float soundVolume);
		void Play(sf::Music &music, float soundVolume);

		void Mute();
		void UnMute();

		bool IsMuted();
		bool IsLoaded();

		void SetVolume(float volume);
		float GetVolume();

	private:

		float musicVolume = 100.0f;
		bool muted = true;
		bool loaded = false;
	};
}