#include "src/hpp/InputManager.hpp"
#include "src/hpp/SoundManager.hpp"
#include <iostream>

namespace hgw
{
	bool InputManager::IsSpriteClicked(sf::Sprite object,
		sf::Event::EventType eventType, sf::RenderWindow &window)
	{
		if (eventType == sf::Event::EventType::MouseButtonPressed)
		{
			sf::IntRect tempRect(object.getPosition().x,
				object.getPosition().y, object.getGlobalBounds().width,
				object.getGlobalBounds().height);

			if (tempRect.contains(sf::Mouse::getPosition(window)))
			{
				std::cout << "Clicked " << std::endl;
				return true;
			}
		}

		return false;
	}

	bool InputManager::IsSpritePressed(sf::Sprite object,
		sf::Mouse::Button button, sf::RenderWindow &window)
	{
		if (sf::Mouse::isButtonPressed(button))
		{
			sf::IntRect tempRect(object.getPosition().x,
				object.getPosition().y, object.getGlobalBounds().width + 1,
				object.getGlobalBounds().height);

			if (tempRect.contains(sf::Mouse::getPosition(window)))
			{
				std::cout << "Pressed" << std::endl;
				return true;
			}
		}

		return false;
	}

	bool InputManager::IsSpriteClicked(sf::IntRect rect, sf::Event::EventType eventType, sf::RenderWindow &window)
	{
		if (eventType == sf::Event::EventType::MouseButtonPressed && rect.contains(sf::Mouse::getPosition(window)))
		{
			return true;
		}
		return false;
	}

	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow &window)
	{
		return sf::Mouse::getPosition(window);
	}
}