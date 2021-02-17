#include <sstream>
#include <iostream>

#include "src/hpp/DEFINITIONS.hpp"
#include "src/hpp/States/PauseState.hpp"
#include "src/hpp/States/GameState2P.hpp"
#include "src/hpp/States/MainMenuState.hpp"

namespace hgw
{
	PauseState::PauseState(GameDataRef data) : _data(data)
	{

	}

	void PauseState::Init()
	{
		this->_data->assets.LoadTexture("Pause Background", PAUSE_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Resume Button", RESUME_BUTTON);
		this->_data->assets.LoadTexture("Home Button", HOME_BUTTON);

		this->_background.setTexture(this->_data->assets.GetTexture("Pause Background"));
		this->_resumeButton.setTexture(this->_data->assets.GetTexture("Resume Button"));
		this->_homeButton.setTexture(this->_data->assets.GetTexture("Home Button"));

		this->_resumeButton.setPosition((this->_data->window.getSize().x / 2) -
			(this->_resumeButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 3) -
			(this->_resumeButton.getLocalBounds().height / 3));

		this->_homeButton.setPosition((this->_data->window.getSize().x / 2) -
			(this->_homeButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 3 * 2) -
			(this->_homeButton.getLocalBounds().height / 3));
	}

	void PauseState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			if (this->_data->input.IsSpriteClicked(this->_resumeButton, event.type,	this->_data->window))
			{
				this->_data->sounds.Play(this->_data->sounds.ClickSound1);
				this->_data->machine.RemoveState();
			}

			if (this->_data->input.IsSpriteClicked(this->_homeButton, event.type, this->_data->window))
			{
				this->_data->sounds.Play(this->_data->sounds.ClickSound1);
				this->_data->machine.RemoveState();
				this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
			}
		}
	}

	void PauseState::Update(float dt)
	{

	}

	void PauseState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_resumeButton);
		this->_data->window.draw(this->_homeButton);

		this->_data->window.display();
	}
}