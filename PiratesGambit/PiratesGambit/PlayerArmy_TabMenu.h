#pragma once
#include "Army.h"
#include"Includes.h"
#include "TacticsArmySlot.h"

class PlayerArmy_TabMenu
{
public:
	PlayerArmy_TabMenu(const std::unique_ptr<Army>& _army, sf::RectangleShape _pos);

	void UpdateUnitAmount(const std::unique_ptr<Army>& _army);

	void Update();
	void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;
private:
	sf::RectangleShape background;
	std::vector<std::unique_ptr<TacticsArmySlot>> armySlots;
};

