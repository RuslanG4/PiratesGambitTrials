#include "BattleActionUI.h"

BattleActionUI::BattleActionUI()
{
	sf::Vector2f attackButtonPos = sf::Vector2f(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100);

	attackButton = std::make_unique<BattleActionButton>(attackButtonPos, TextureManager::getInstance().getTexture("SWORD_ICON"));
	waitButton = std::make_unique<BattleActionButton>(sf::Vector2f(attackButtonPos.x - 175, attackButtonPos.y), TextureManager::getInstance().getTexture("WAIT_ICON"));

	currentMode.setFont(TextureManager::getInstance().getFont("Comic"));
	currentMode.setString("Tactics Mode");
	currentMode.setPosition(250, 50);
}

void BattleActionUI::render(const std::unique_ptr<sf::RenderWindow>& _win) const
{
	attackButton->render(_win);
	waitButton->render(_win);
	_win->draw(currentMode);
}

void BattleActionUI::update()
{
	attackButton->update();
	waitButton->update();
}
