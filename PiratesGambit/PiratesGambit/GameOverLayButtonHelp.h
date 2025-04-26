#pragma once
#include "Includes.h"
#include"TextureManager.h"
class GameOverLayButtonHelp
{
public:
	GameOverLayButtonHelp(const std::string& textString, const sf::Texture& texture);
	void setPosition(sf::Vector2f _pos);
	void render(const std::unique_ptr<sf::RenderWindow>& _win) const;
private:
	sf::Text text;
	sf::Sprite sprite;
};

