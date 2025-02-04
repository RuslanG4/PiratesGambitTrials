#pragma once
#include"PlayerArmy_TabMenu.h"

class PlayerTabMenu
{
public:
	PlayerTabMenu(const std::unique_ptr<Army>& _army);

	void Update();
	void Render(const std::unique_ptr<sf::RenderWindow>& _win) const;

	void Interact(const std::unique_ptr<Army>& _army);
	void OpenMenu() { isOpen = true; }
	void CloseMenu() { isOpen = false; }

	void UpdateUnitAmountUI(const std::unique_ptr<Army>& _army);

private:
	sf::RectangleShape background;
	std::unique_ptr<PlayerArmy_TabMenu> armyMenu;

	bool isOpen{ false };
};

