#pragma once
#include"GameOverLayButtonHelp.h"
class GameOverLay
{
public:
	GameOverLay();
	~GameOverLay() = default;

	void Render(const std::unique_ptr<sf::RenderWindow>& _win) const;
private:
	std::unique_ptr<GameOverLayButtonHelp> tabMenu;
	std::unique_ptr<GameOverLayButtonHelp> mapMenu;
	std::unique_ptr<GameOverLayButtonHelp> changeCannons;
	std::unique_ptr<GameOverLayButtonHelp> SpaceKey;
};

