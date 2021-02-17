#include "src/hpp/AssetManager.hpp"

namespace hgw
{
	void AssetManager::LoadTexture(std::string name, std::string filename, bool setSmooth)
	{
		sf::Texture tex;

		if (tex.loadFromFile(filename))
		{
			this->_textures[name] = tex;
			_textures[name].setSmooth(setSmooth);
		}
	}
	sf::Texture &AssetManager::GetTexture(std::string name)
	{
		return this->_textures.at(name);
	}

	void AssetManager::LoadFont(std::string name, std::string filename)
	{
		sf::Font font;

		if (font.loadFromFile(filename))
		{
			this->_fonts[name] = font;
		}
	}
	sf::Font &AssetManager::GetFont(std::string name)
	{
		return this->_fonts.at(name);
	}
}