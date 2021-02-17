#include <sstream>
#include <iostream>

#include "src/hpp/DEFINITIONS.hpp"

#include "src/hpp/States/GameOverState.hpp"
#include "src/hpp/States/GameState2P.hpp"
#include "src/hpp/States/GameState1P.hpp"
#include "src/hpp/States/MainMenuState.hpp"
#include <SFML/Audio.hpp>
#include "src/hpp/SoundManager.hpp"

namespace hgw
{
	GameOverState::GameOverState(GameDataRef data, int gs, bool isPlayingVsAI, int diff) : _data(data), gameState(gs), vsAI(isPlayingVsAI), difficulty(diff)
	{

	}

	void GameOverState::Init()
	{

		this->_data->assets.LoadTexture("Retry Button", RETRY_BUTTON);
		this->_data->assets.LoadTexture("Home Button", HOME_BUTTON);

		switch (gameState)
		{
		case STATE_WON:
			this->_data->assets.LoadTexture("Game Over X Won", GAME_OVER_X_WON_FILEPATH);
			this->_result.setTexture(this->_data->assets.GetTexture("Game Over X Won"));
			break;
		case STATE_LOSE:
			std::cout << "O WON" << std::endl;
			this->_data->assets.LoadTexture("Game Over O Won", GAME_OVER_O_WON_FILEPATH);
			this->_result.setTexture(this->_data->assets.GetTexture("Game Over O Won"));
			break;
		case STATE_DRAW:
			this->_data->assets.LoadTexture("Game Over Draw", GAME_OVER_DRAW_FILEPATH);
			this->_result.setTexture(this->_data->assets.GetTexture("Game Over Draw"));
			std::cout << "Draw" << std::endl;
			break;
		}

		this->_retryButton.setTexture(this->_data->assets.GetTexture("Retry Button"));
		this->_homeButton.setTexture(this->_data->assets.GetTexture("Home Button"));

		this->_retryButton.setPosition((SCREEN_WIDTH / 1.75f) - (this->_retryButton.getGlobalBounds().width / 1.75f),
			(SCREEN_HEIGHT / 2) - (this->_retryButton.getGlobalBounds().height / 4));

		this->_homeButton.setPosition((SCREEN_WIDTH / 2) - (this->_homeButton.getGlobalBounds().width / 2),
			(this->_homeButton.getGlobalBounds().height * 5));

		this->_result.setPosition((SCREEN_WIDTH / 2) - (this->_result.getGlobalBounds().width / 2), 0);

	}

	void GameOverState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			if (this->_data->input.IsSpriteClicked(this->_retryButton, event.type, this->_data->window))
			{
				this->_data->sounds.Play(this->_data->sounds.ClickSound1);
				if (vsAI)
				{
					this->_data->machine.AddState(StateRef(new GameState1P(_data, difficulty)), true);
				}
				else
				{
					this->_data->machine.AddState(StateRef(new GameState2P(_data)), true);
				}
			}

			if (this->_data->input.IsSpriteClicked(this->_homeButton, event.type, this->_data->window))
			{
				this->_data->sounds.Play(this->_data->sounds.ClickSound1);
				this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
			}
		}
	}

	void GameOverState::Update(float dt)
	{

	}

	void GameOverState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color(224, 161, 86, 255));

		this->_data->window.draw(this->_result);
		this->_data->window.draw(this->_retryButton);
		this->_data->window.draw(this->_homeButton);

		this->_data->window.display();
	}
}