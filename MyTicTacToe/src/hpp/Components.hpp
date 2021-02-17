#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"

namespace hgw
{
	namespace cmp
	{
		class VolumeBar
		{
		public:
			VolumeBar(GameDataRef data);

			sf::Sprite _bar;
			sf::Sprite _point;

			void Init();

			void Attach(sf::Sprite sprite, sf::Vector2f posDifference, float volume);
			void MovePoint();
			float GetVolume();
			
		private:
			GameDataRef _data;
		};
	}
}