#include <iostream>

#include "src/hpp/DEFINITIONS.hpp"
#include "src/hpp/States/SettingsState.hpp"
#include "src/hpp/States/MainMenuState.hpp"

namespace hgw
{
	SettingsState::SettingsState(GameDataRef data, int *diff) : _data(data), difficulty(diff)
	{
		
	}

	void SettingsState::Init()
	{
		this->_musicBar.Init();
		this->_soundBar.Init();

		this->_data->assets.LoadTexture("Backgound", MAIN_MENU_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Settings", SETTINGS_ICON_FILEPATH);
		this->_data->assets.LoadTexture("Difficulty", SETTINGS_AI_DIFFICULTY_FILEPATH);

		this->_data->assets.LoadTexture("Music On", SETTINGS_MUSIC_ON_ICON_FILEPATH);
		this->_data->assets.LoadTexture("Music Off", SETTINGS_MUSIC_OFF_ICON_FILEPATH);
		this->_data->assets.LoadTexture("Sound On", SETTINGS_SOUND_ON_ICON_FILEPATH);
		this->_data->assets.LoadTexture("Sound Off", SETTINGS_SOUND_OFF_ICON_FILEPATH);

		this->_data->assets.LoadTexture("Easy Diff", SETTINGS_DIFFICULTY_EASY_FILEPATH);
		this->_data->assets.LoadTexture("Medium Diff", SETTINGS_DIFFICULTY_MEDIUM_FILEPATH);
		this->_data->assets.LoadTexture("Impossible Diff", SETTINGS_DIFFICULTY_IMPOSSIBLE_FILEPATH);
		this->_data->assets.LoadTexture("Easy Diff Selected", SETTINGS_DIFFICULTY_EASY_SELECETED_FILEPATH);
		this->_data->assets.LoadTexture("Medium Diff Selected", SETTINGS_DIFFICULTY_MEDIUM_SELECETED_FILEPATH);
		this->_data->assets.LoadTexture("Impossible Diff Selected", SETTINGS_DIFFICULTY_IMPOSSIBLE_SELECETED_FILEPATH);

		this->_easyDiff.setTexture(this->_data->assets.GetTexture("Easy Diff"));
		this->_mediumDiff.setTexture(this->_data->assets.GetTexture("Medium Diff"));
		this->_impossibleDiff.setTexture(this->_data->assets.GetTexture("Impossible Diff"));

		this->_settings.setTexture(this->_data->assets.GetTexture("Settings"));
		this->_background.setTexture(this->_data->assets.GetTexture("Background"));

		this->_difficultyText.setTexture(this->_data->assets.GetTexture("Difficulty"));

		if (this->_data->sounds.IsMuted())
		{
			this->_sound.setTexture(this->_data->assets.GetTexture("Sound Off"));
		}
		else
		{
			this->_sound.setTexture(this->_data->assets.GetTexture("Sound On"));
		}

		if (this->_data->music.IsMuted())
		{
			this->_music.setTexture(this->_data->assets.GetTexture("Music Off"));
		}
		else
		{
			this->_music.setTexture(this->_data->assets.GetTexture("Music On"));
		}


		if (*difficulty == AI_DIFFICULTY_EASY)
		{
			this->_easyDiff.setTexture(this->_data->assets.GetTexture("Easy Diff Selected"));
		}
		else if (*difficulty == AI_DIFFICULTY_MEDIUM)
		{
			this->_mediumDiff.setTexture(this->_data->assets.GetTexture("Medium Diff Selected"));
		}
		else if (*difficulty == AI_DIFFICULTY_IMPOSSIBLE)
		{
			this->_impossibleDiff.setTexture(this->_data->assets.GetTexture("Impossible Diff Selected"));
			this->_impossibleDiff.setColor(sf::Color::Red);
		}

		this->_sound.setPosition((SCREEN_WIDTH / 2) + (this->_sound.getGlobalBounds().width / 1.5f),
			(SCREEN_HEIGHT / 8) - (this->_sound.getGlobalBounds().height / 2));

		this->_music.setPosition((SCREEN_WIDTH / 4) - (this->_music.getGlobalBounds().width / 1.5f),
			(SCREEN_HEIGHT / 8) - (this->_music.getGlobalBounds().height / 2));

		this->_settings.setPosition((this->_data->window.getSize().x / 2) - (this->_settings.getLocalBounds().width / 2),
			(this->_data->window.getSize().y) - (this->_settings.getLocalBounds().height * 1.90f));
		
		this->_soundBar.Attach(this->_sound, sf::Vector2f(0, 60), this->_data->sounds.GetVolume());
		this->_musicBar.Attach(this->_music, sf::Vector2f(0, 60), this->_data->music.GetVolume());

		this->_difficultyText.setPosition((SCREEN_WIDTH / 2) - (this->_difficultyText.getLocalBounds().width / 2),
			(SCREEN_HEIGHT / 4) - (this->_difficultyText.getLocalBounds().height / 2));

		this->_easyDiff.setOrigin(this->_easyDiff.getGlobalBounds().width / 2, this->_easyDiff.getGlobalBounds().height / 2);
		this->_mediumDiff.setOrigin(this->_easyDiff.getGlobalBounds().width / 2, this->_easyDiff.getGlobalBounds().height / 2);
		this->_impossibleDiff.setOrigin(this->_easyDiff.getGlobalBounds().width / 2, this->_easyDiff.getGlobalBounds().height / 2);

		this->_easyDiff.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2.7);
		this->_mediumDiff.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2.3);
		this->_impossibleDiff.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}

	void SettingsState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			if (this->_data->input.IsSpriteClicked(this->_sound, event.type, this->_data->window))
			{
				if (this->_data->sounds.IsMuted())
				{
					this->_data->sounds.UnMute();
					this->_data->sounds.Play(this->_data->sounds.ClickSound1);

					this->_sound.setTexture(this->_data->assets.GetTexture("Sound On"));
				}
				else
				{
					this->_data->sounds.Mute();
					this->_data->sounds.Play(this->_data->sounds.ClickSound1);

					this->_sound.setTexture(this->_data->assets.GetTexture("Sound Off"));
				}
			}
			else if (this->_data->input.IsSpriteClicked(this->_music, event.type, this->_data->window))
			{
				if (this->_data->music.IsMuted())
				{
					this->_data->sounds.Play(this->_data->sounds.ClickSound1);

					if (this->_data->music.IsLoaded())
					{
						this->_data->music.gameMusic.stop();
						this->_data->music.UnMute();
						this->_data->music.gameMusic.play();
					}
					else
					{
						this->_data->music.UnMute();
						this->_data->music.LoopPlay(this->_data->music.gameMusic, this->_data->music.GetVolume());
					}	

					this->_music.setTexture(this->_data->assets.GetTexture("Music On"));
				}
				else
				{
					this->_data->sounds.Play(this->_data->sounds.ClickSound1);

					this->_data->music.gameMusic.stop();
					this->_data->music.Mute();

					this->_music.setTexture(this->_data->assets.GetTexture("Music Off"));
				}
			}
			else if (this->_data->input.IsSpriteClicked(this->_settings, event.type, this->_data->window))
			{
				this->_data->sounds.Play(this->_data->sounds.ClickSound1);
				this->_data->machine.RemoveState();
			}
			
			if (this->_data->input.IsSpritePressed((this->_soundBar._bar), sf::Mouse::Left, this->_data->window))
			{
				this->_soundBar.MovePoint();
				this->_data->sounds.SetVolume(this->_soundBar.GetVolume());
				std::cout << this->_data->sounds.GetVolume() << "<- sound volume" << std::endl;
			}
			else if (this->_data->input.IsSpritePressed((this->_musicBar._bar), sf::Mouse::Left, this->_data->window))
			{
				this->_musicBar.MovePoint();
				this->_data->music.SetVolume(this->_musicBar.GetVolume());
				std::cout << this->_data->music.GetVolume() << " <- music volume" << std::endl;
			}

			if(this->_data->input.IsSpriteClicked(sf::IntRect(this->_easyDiff.getPosition().x - EASY_WIDTH / 2,
				this->_easyDiff.getPosition().y - EASY_HEIGHT / 2, EASY_WIDTH, EASY_HEIGHT), event.type, this->_data->window))
			{
				if (*difficulty != AI_DIFFICULTY_EASY)
				{
					this->_data->sounds.Play(this->_data->sounds.ClickSound1);

					this->_easyDiff.setTexture(this->_data->assets.GetTexture("Easy Diff Selected"));
					this->_mediumDiff.setTexture(this->_data->assets.GetTexture("Medium Diff"));
					this->_impossibleDiff.setTexture(this->_data->assets.GetTexture("Impossible Diff"));
					*difficulty = AI_DIFFICULTY_EASY;
				}
			}
			if(this->_data->input.IsSpriteClicked(sf::IntRect(this->_mediumDiff.getPosition().x - MEDIUM_WIDTH / 2,
				this->_mediumDiff.getPosition().y - MEDIUM_HEIGHT / 2, MEDIUM_WIDTH, MEDIUM_HEIGHT), event.type, this->_data->window))
			{
				if (*difficulty != AI_DIFFICULTY_MEDIUM)
				{
					this->_data->sounds.Play(this->_data->sounds.ClickSound1);

					this->_easyDiff.setTexture(this->_data->assets.GetTexture("Easy Diff"));
					this->_mediumDiff.setTexture(this->_data->assets.GetTexture("Medium Diff Selected"));
					this->_impossibleDiff.setTexture(this->_data->assets.GetTexture("Impossible Diff"));
					*difficulty = AI_DIFFICULTY_MEDIUM;
				}
			}
			if (this->_data->input.IsSpriteClicked(sf::IntRect(this->_impossibleDiff.getPosition().x - IMPOSSIBLE_WIDTH / 2,
				this->_impossibleDiff.getPosition().y - IMPOSSIBLE_HEIGHT / 2, IMPOSSIBLE_WIDTH, IMPOSSIBLE_HEIGHT), event.type, this->_data->window))
			{
				if (*difficulty != AI_DIFFICULTY_IMPOSSIBLE)
				{
					this->_data->sounds.Play(this->_data->sounds.ClickSound1);

					this->_easyDiff.setTexture(this->_data->assets.GetTexture("Easy Diff"));
					this->_mediumDiff.setTexture(this->_data->assets.GetTexture("Medium Diff"));
					this->_impossibleDiff.setTexture(this->_data->assets.GetTexture("Impossible Diff Selected"));
					this->_impossibleDiff.setColor(sf::Color::Red);
					*difficulty = AI_DIFFICULTY_IMPOSSIBLE;
				}
			}
		}
	}

	void SettingsState::Update(float dt)
	{

	}

	void SettingsState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_music);
		this->_data->window.draw(this->_sound);
		this->_data->window.draw(this->_settings);

		this->_data->window.draw(this->_musicBar._bar);
		this->_data->window.draw(this->_musicBar._point);
		this->_data->window.draw(this->_soundBar._bar);
		this->_data->window.draw(this->_soundBar._point);

		this->_data->window.draw(this->_difficultyText);
		this->_data->window.draw(this->_easyDiff);
		this->_data->window.draw(this->_mediumDiff);
		this->_data->window.draw(this->_impossibleDiff);

		this->_data->window.display();
	}
}