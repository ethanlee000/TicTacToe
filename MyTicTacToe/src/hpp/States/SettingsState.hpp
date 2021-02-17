#pragma once

#include <SFML/Graphics.hpp>
#include "src/hpp/State.hpp"
#include "src/hpp/Game.hpp"
#include "src/hpp/Components.hpp"

namespace hgw
{
	class SettingsState : public State
	{
	public:
		SettingsState(GameDataRef data, int *diff);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::Sprite _sound;
		sf::Sprite _music;
		sf::Sprite _settings;

		sf::Sprite _difficultyText;
		sf::Sprite _easyDiff, _mediumDiff, _impossibleDiff;

		cmp::VolumeBar _musicBar{ _data };
		cmp::VolumeBar _soundBar{ _data };

		int *difficulty;
	};
}