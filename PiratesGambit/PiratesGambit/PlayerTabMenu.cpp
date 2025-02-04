#include "PlayerTabMenu.h"

PlayerTabMenu::PlayerTabMenu(const std::unique_ptr<Army>& _army)
{
	background.setSize(sf::Vector2f(620, 800));
	background.setFillColor(sf::Color::Blue);
	background.setPosition(100, 100);
	armyMenu = std::make_unique<PlayerArmy_TabMenu>(_army, background);
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
	}
}

void PlayerTabMenu::Interact(const std::unique_ptr<Army>& _army)
{
	if(!isOpen)
	{
		OpenMenu();
		UpdateUnitAmountUI(_army);
	}else
	{
		CloseMenu();
	}
}

void PlayerTabMenu::UpdateUnitAmountUI(const std::unique_ptr<Army>& _army)
{
	armyMenu->UpdateUnitAmount(_army);
}
