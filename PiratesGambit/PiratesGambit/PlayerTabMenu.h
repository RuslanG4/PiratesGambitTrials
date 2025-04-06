#pragma once
#include "Player.h"
#include"PlayerArmy_TabMenu.h"
#include"Resources_TabMenu.h"

class PlayerTabMenu
{
public:
	PlayerTabMenu(const std::unique_ptr<Army>& _army, const std::unique_ptr<Inventory>& _inventory);

	void Update();
	void Render(const std::unique_ptr<sf::RenderWindow>& _win) const;

	void Interact(const std::shared_ptr<Player>& _player);
	static void OpenMenu() { isOpen = true; }
	static void CloseMenu() { isOpen = false; }

	void UpdateSlots(const std::unique_ptr<Army>& _army);
	void UpdateUnitAmountUI(const std::unique_ptr<Army>& _army);
	void UpdateResourcesUI(const std::unique_ptr<Inventory>& _inventory);

	static bool isMenuOpen() { return isOpen; }

private:
	sf::Sprite background;
	std::unique_ptr<PlayerArmy_TabMenu> armyMenu;
	std::unique_ptr<Resources_TabMenu> resourcesMenu;

	sf::Clock buttonClock;

	static bool isOpen;
};

