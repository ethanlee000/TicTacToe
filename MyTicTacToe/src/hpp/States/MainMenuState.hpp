#pragma once

#include <SFML/Graphics.hpp>
#include "src/hpp/State.hpp"
#include "src/hpp/Game.hpp"

namespace hgw
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::Sprite _1pPlayButton;
		sf::Sprite _2pPlayButton;
		sf::Sprite _title;
		sf::Sprite _settings;

		sf::Sprite _sound;
		sf::Sprite _music;

		static int difficulty;
	};
}