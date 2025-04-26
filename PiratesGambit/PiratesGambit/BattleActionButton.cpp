#include "BattleActionButton.h"

BattleActionButton::BattleActionButton(sf::Vector2f _pos, sf::Texture& _texture)
{
	uiBorder.setTexture(TextureManager::getInstance().getTexture("ACTION_BORDER"));
	attackSprite.setTexture(_texture);

	uiBorder.setOrigin(24, 24);
	uiBorder.setScale(3, 3);
	attackSprite.setOrigin(16, 16);
	attackSprite.setScale(3, 3);

	uiBorder.setPosition(_pos);
	attackSprite.setPosition(uiBorder.getPosition());
}

void BattleActionButton::render(const std::unique_ptr<sf::RenderWindow>& _win) const
{
	_win->draw(uiBorder);
	_win->draw(attackSprite);
}

void BattleActionButton::update()
{
	buttonPressed = false;
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getInstance().getMousePosition());
	if (uiBorder.getGlobalBounds().contains(mousePos))
	{
		uiBorder.setColor(sf::Color(150, 150, 150)); // Darken
		attackSprite.setColor(sf::Color(150, 150, 150)); // Darken
		if (Mouse::getInstance().LeftClicked())
		{
			buttonPressed = true;
			uiBorder.setColor(sf::Color::White);
			attackSprite.setColor(sf::Color::White);
		}
	}
	else
	{
		uiBorder.setColor(sf::Color::White);
		attackSprite.setColor(sf::Color::White);
	}

}
