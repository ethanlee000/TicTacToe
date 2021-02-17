#pragma once

#include <SFML/Graphics.hpp>

namespace hgw
{
	class InputManager
	{
	public:
		InputManager() {}
		~InputManager() {}

		//returns true if sprite was clicked
		bool IsSpriteClicked(sf::Sprite object, sf::Event::EventType eventType, sf::RenderWindow &window);
		bool IsSpriteClicked(sf::IntRect rect, sf::Event::EventType eventType, sf::RenderWindow &window);

		//returns true if sprite was clicked and held
		bool IsSpritePressed(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);

		sf::Vector2i GetMousePosition(sf::RenderWindow &window);
	};
}