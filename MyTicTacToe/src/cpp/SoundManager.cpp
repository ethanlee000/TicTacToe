#include "src/hpp/SoundManager.hpp"
#include "src/hpp/DEFINITIONS.hpp"
#include <iostream>

namespace hgw
{
	void SoundManager::Init()
	{
		if (!muted && !isLoaded)
		{
			LoadFromFile();
			SetBuffers();
			isLoaded = true;
		}
	}

	void SoundManager::LoadFromFile()
	{
		StartGameBuffer.loadFromFile(START_GAME_CLICK_SOUND_FILEPATH);
		GridClickBuffer.loadFromFile(GRID_CLICK_SOUND_FILEPATH);
		ClickBuffer1.loadFromFile(CLICK_SOUND_1_FILEPATH);
		ClickBuffer2.loadFromFile(CLICK_SOUND_2_FILEPATH);
	}

	void SoundManager::SetBuffers()
	{
		StartGameSound.setBuffer(StartGameBuffer);
		GridClickSound.setBuffer(GridClickBuffer);
		ClickSound1.setBuffer(ClickBuffer1);
		ClickSound2.setBuffer(ClickBuffer2); 
	}

	void SoundManager::Play(sf::Sound &sound)
	{
		if (muted)
		{
			std::cout << "Song Muted" << std::endl;
		}
		else 
		{ 
			if (sound.getVolume() != soundVolume)
			{
				sound.setVolume(soundVolume);
			}
			sound.play();
		}
	}

	void SoundManager::Mute() 
	{
		if (muted)
		{
			std::cout << "Alredy muted" << std::endl;
		}
		else
		{
			muted = true;
		}
	}
	void SoundManager::UnMute()
	{
		if (!muted)
		{
			std::cout << "Alredy unmuted" << std::endl;
		}
		else
		{
			muted = false;
			if (!isLoaded)
			{
				Init();
			}
		}
	}

	bool SoundManager::IsMuted()
	{
		return muted;
	}

	void SoundManager::SetVolume(float volume)
	{
		soundVolume = volume;
	}

	float SoundManager::GetVolume()
	{
		return soundVolume;
	}
}