#include <sstream>
#include <iostream>

#include "src/hpp/DEFINITIONS.hpp"

#include "src/hpp/States/MainMenuState.hpp"
#include "src/hpp/States/GameState2P.hpp"
#include "src/hpp/States/GameState1P.hpp"
#include "src/hpp/States/SettingsState.hpp"

namespace hgw
{
	// add setsmoth() to textres
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{
		this->_data->music.LoopPlay(this->_data->music.gameMusic, 60.0f);
	}

	void MainMenuState::Init()
	{
		this->_data->assets.LoadTexture("Background", MAIN_MENU_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("1P Play Button", MAIN_MENU_1P_PLAY_BUTTON);
		this->_data->assets.LoadTexture("2P Play Button", MAIN_MENU_2P_PLAY_BUTTON);
		this->_data->assets.LoadTexture("Game Title", MAIN_MENU_TITLE_PATH);
		this->_data->assets.LoadTexture("Settings", SETTINGS_ICON_FILEPATH);

		this->_data->assets.LoadTexture("Music On", SETTINGS_MUSIC_ON_ICON_FILEPATH);
		this->_data->assets.LoadTexture("Music Off", SETTINGS_MUSIC_OFF_ICON_FILEPATH);
		this->_data->assets.LoadTexture("Sound On", SETTINGS_SOUND_ON_ICON_FILEPATH);
		this->_data->assets.LoadTexture("Sound Off", SETTINGS_SOUND_OFF_ICON_FILEPATH);

		this->_background.setTexture(this->_data->assets.GetTexture("Background"));
		this->_1pPlayButton.setTexture(this->_data->assets.GetTexture("1P Play Button"));
		this->_2pPlayButton.setTexture(this->_data->assets.GetTexture("2P Play Button"));
		this->_title.setTexture(this->_data->assets.GetTexture("Game Title"));
		this->_settings.setTexture(this->_data->assets.GetTexture("Settings"));

		this->_sound.setTexture(this->_data->assets.GetTexture("Sound On"));
		this->_music.setTexture(this->_data->assets.GetTexture("Music On"));

		this->_1pPlayButton.setPosition((SCREEN_WIDTH / 1.75f) - (this->_1pPlayButton.getGlobalBounds().width / 1.75f),
			(SCREEN_HEIGHT / 2) - (this->_1pPlayButton.getGlobalBounds().height / 2));

		this->_2pPlayButton.setPosition((SCREEN_WIDTH / 2) - (this->_2pPlayButton.getGlobalBounds().width / 2),
			(this->_2pPlayButton.getGlobalBounds().height * 3.5f));

		this->_title.setPosition((SCREEN_WIDTH / 2) - (this->_title.getGlobalBounds().width / 2),
			(this->_title.getGlobalBounds().height * 0.1f));

		this->_settings.setPosition((this->_data->window.getSize().x / 2) - (this->_settings.getLocalBounds().width / 2),
			(this->_data->window.getSize().y) - (this->_settings.getLocalBounds().height * 1.90f));
	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			if (this->_data->input.IsSpriteClicked(this->_2pPlayButton, event.type, this->_data->window))
			{
				this->_data->sounds.Play(this->_data->sounds.StartGameSound);
				this->_data->machine.AddState(StateRef(new GameState2P(_data)), true);
			}
			else if (this->_data->input.IsSpriteClicked(this->_1pPlayButton, event.type, this->_data->window))
			{
				this->_data->sounds.Play(this->_data->sounds.StartGameSound);

				this->_data->machine.AddState(StateRef(new GameState1P(_data, difficulty)), true);
			}
			else if (this->_data->input.IsSpriteClicked(this->_settings, event.type, this->_data->window))
			{
				this->_data->sounds.Play(this->_data->sounds.ClickSound1);
				this->_data->machine.AddState(StateRef(new SettingsState(_data, &difficulty)), false);
			}
		}
	}

	void MainMenuState::Update(float dt)
	{

	}

	void MainMenuState::Draw(float dt)
	{
		this->_data->window.clear();
		
		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_1pPlayButton);
		this->_data->window.draw(this->_2pPlayButton);
		this->_data->window.draw(this->_title);
		this->_data->window.draw(this->_settings);

		this->_data->window.display();
	}

	int MainMenuState::difficulty = AI_DIFFICULTY_EASY;
}