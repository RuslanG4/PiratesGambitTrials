#include "GameOverLay.h"

GameOverLay::GameOverLay()
{
	SpaceKey = std::make_unique<GameOverLayButtonHelp>("Fire Cannons", TextureManager::getInstance().getTexture("SPACE_KEY"));
	SpaceKey->setPosition(sf::Vector2f(0, 50));
	tabMenu = std::make_unique<GameOverLayButtonHelp>("Player Inventory", TextureManager::getInstance().getTexture("TAB_KEY"));
	tabMenu->setPosition(sf::Vector2f(0, 100));
	mapMenu = std::make_unique<GameOverLayButtonHelp>("Open Map", TextureManager::getInstance().getTexture("M_KEY"));
	mapMenu->setPosition(sf::Vector2f(0, 150));
	changeCannons = std::make_unique<GameOverLayButtonHelp>("Change Cannons", TextureManager::getInstance().getTexture("EQ_KEY"));
	changeCannons->setPosition(sf::Vector2f(0, 200));
}

void GameOverLay::Render(const std::unique_ptr<sf::RenderWindow>& _win) const
{
	_win->setView(_win->getDefaultView());
	SpaceKey->render(_win);
	tabMenu->render(_win);
	mapMenu->render(_win);
	changeCannons->render(_win);
}
