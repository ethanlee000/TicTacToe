#pragma once

#include <SFML/Audio.hpp>
#include <map>

namespace hgw
{
	class SoundManager
	{
	public:
		SoundManager() {};
		~SoundManager() {};

		sf::Sound StartGameSound;
		sf::Sound GridClickSound;
		sf::Sound ClickSound1;
		sf::Sound ClickSound2;

		void Init();

		void Play(sf::Sound &sound);

		void Mute();
		void UnMute();
		bool IsMuted();

		void SetVolume(float volume);
		float GetVolume();

	private:
		sf::SoundBuffer StartGameBuffer;
		sf::SoundBuffer GridClickBuffer;
		sf::SoundBuffer ClickBuffer1;
		sf::SoundBuffer ClickBuffer2;

		float soundVolume = 100.0f;

		bool muted = false;
		bool isLoaded = false;

		void LoadFromFile();
		void SetBuffers();
	};

}