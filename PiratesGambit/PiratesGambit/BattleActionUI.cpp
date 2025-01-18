#include "BattleActionUI.h"

BattleActionUI::BattleActionUI()
{
	uiBorder.setTexture(TextureManager::getInstance().getTexture("ACTION_BORDER"));
	attackSprite.setTexture(TextureManager::getInstance().getTexture("SWORD_ICON"));

	uiBorder.setOrigin(24, 24);
	uiBorder.setScale(3, 3);
	attackSprite.setOrigin(16, 16);
	attackSprite.setScale(3, 3);

	uiBorder.setPosition(sf::Vector2f(SCREEN_WIDTH - uiBorder.getGlobalBounds().width, SCREEN_HEIGHT - uiBorder.getGlobalBounds().height));
	attackSprite.setPosition(uiBorder.getPosition());

	currentMode.setFont(TextureManager::getInstance().getFont());
	currentMode.setString("Tactics Mode");
	currentMode.setPosition(250, 50);
}

void BattleActionUI::render(const std::unique_ptr<sf::RenderWindow>& _win) const
{
	_win->draw(uiBorder);
	_win->draw(attackSprite);
	_win->draw(currentMode);
}

void BattleActionUI::update()
{
	buttonPressed = false;
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getInstance().getMousePosition());
	if(uiBorder.getGlobalBounds().contains(mousePos))
	{
		uiBorder.setColor(sf::Color(150, 150, 150)); // Darken
		attackSprite.setColor(sf::Color(150, 150, 150)); // Darken
		if (Mouse::getInstance().LeftClicked())
		{
			buttonPressed = true;
			uiBorder.setColor(sf::Color::White);
			attackSprite.setColor(sf::Color::White);
		}
	}else
	{
		uiBorder.setColor(sf::Color::White); 
		attackSprite.setColor(sf::Color::White);
	}
	
}
