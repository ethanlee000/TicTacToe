#pragma once

#include <SFML/Graphics.hpp>
#include "src/hpp/State.hpp"
#include "src/hpp/Game.hpp"

namespace hgw
{
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef data, int gameState, bool isPlayingVsAI, int diff);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	private:
		GameDataRef _data;

		sf::Sprite _retryButton;
		sf::Sprite _homeButton;
		sf::Sprite _result;

		int gameState;
		bool vsAI;
		int difficulty;
	};
}