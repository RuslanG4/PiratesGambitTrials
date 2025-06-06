#include "PlayerTabMenu.h"

bool PlayerTabMenu::isOpen = false;

PlayerTabMenu::PlayerTabMenu(const std::unique_ptr<Army>& _army, const std::unique_ptr<Inventory>& _inventory)
{
	background.setTexture(TextureManager::getInstance().getTexture("PLAYER_MENU_UI"));
	background.setScale(7, 8);

	background.setPosition(100, 100);
	armyMenu = std::make_unique<PlayerArmy_TabMenu>(_army, background);
	resourcesMenu = std::make_unique<Resources_TabMenu>(_inventory, background);
}

void PlayerTabMenu::Update()
{
	if(isOpen)
	{
		armyMenu->Update();
	}
}

void PlayerTabMenu::Render(const std::unique_ptr<sf::RenderWindow>& _win) const
{
	if(isOpen){
		_win->setView(_win->getDefaultView());
		_win->draw(background);
		armyMenu->Render(_win);
		resourcesMenu->Render(_win);
	}
}

void PlayerTabMenu::Interact(const std::shared_ptr<Player>& _player)
{
	if(!isOpen)
	{
		OpenMenu();
		UpdateUnitAmountUI(_player->getArmy());
		UpdateSlots(_player->getArmy());
		UpdateResourcesUI(_player->getInventory());
	}else
	{
		CloseMenu();
	}
}

void PlayerTabMenu::RefreshArmyAfterBattle(const std::unique_ptr<Army>& _army)
{
	armyMenu->RefreshSlots(_army);
}

void PlayerTabMenu::UpdateSlots(const std::unique_ptr<Army>& _army)
{
	armyMenu->updateSlot(_army);
}

void PlayerTabMenu::UpdateUnitAmountUI(const std::unique_ptr<Army>& _army)
{
	armyMenu->UpdateUnitAmount(_army);
}

void PlayerTabMenu::UpdateResourcesUI(const std::unique_ptr<Inventory>& _inventory)
{
	resourcesMenu->UpdateMenu(_inventory, background);
}

