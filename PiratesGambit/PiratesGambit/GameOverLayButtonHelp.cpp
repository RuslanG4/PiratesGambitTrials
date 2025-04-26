#include "GameOverLayButtonHelp.h"

GameOverLayButtonHelp::GameOverLayButtonHelp(const std::string& textString, const sf::Texture& texture)
{
	text.setFont(TextureManager::getInstance().getFont("Varsity"));
    text.setString(textString);
    text.setCharacterSize(24); // Example size
    text.setFillColor(sf::Color::White); // Example color

    sprite.setTexture(texture);
}

void GameOverLayButtonHelp::setPosition(sf::Vector2f _pos)
{
    int padding = 50;
    sf::FloatRect textBounds = text.getGlobalBounds();

    sf::Vector2f pos = _pos + sf::Vector2f{ SCREEN_WIDTH - textBounds.width - sprite.getGlobalBounds().width - padding, 0};
    text.setPosition(pos);
    sprite.setPosition(pos.x + textBounds.width + 10.f, pos.y); // 10 pixels padding
}

void GameOverLayButtonHelp::render(const std::unique_ptr<sf::RenderWindow>& _win) const
{
	_win->draw(text);
	_win->draw(sprite);
}
