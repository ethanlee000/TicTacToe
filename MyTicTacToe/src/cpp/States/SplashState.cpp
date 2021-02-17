#include <sstream>
#include <iostream>

#include "src/hpp/DEFINITIONS.hpp"

#include "src/hpp/States/SplashState.hpp"
#include "src/hpp/States/MainMenuState.hpp"
#include "src/hpp/States/GameOverState.hpp"

namespace hgw
{
	SplashState::SplashState(GameDataRef data) : _data(data)
	{

	}

	void SplashState::Init()
	{
		this->_data->sounds.Init();
		this->_data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);

		_background.setTexture(this->_data->assets.GetTexture("Splash State Background"));
	}

	void SplashState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
		}
	}

	void SplashState::Update(float dt)
	{
		if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
		}
	}

	void SplashState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color(224,161,86,255));
		
		this->_data->window.draw(this->_background);

		this->_data->window.display();
	}
}
