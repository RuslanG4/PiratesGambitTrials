#include "PlayerArmy_TabMenu.h"

PlayerArmy_TabMenu::PlayerArmy_TabMenu(const std::unique_ptr<Army>& _army, sf::Sprite _pos)
{
	background.setTexture(TextureManager::getInstance().getTexture("ARMY_MENU_UI"));
	background.setScale(9, 5);

	sf::Vector2f position = sf::Vector2f(_pos.getPosition().x + 84, _pos.getGlobalBounds().height - 280);
	background.setPosition(position);

	position = background.getPosition() + sf::Vector2f(74,80);

	for (int i = 0; i < 7; i++) //7 is max
	{
		if (i == 4)
		{
			if (_army->getArmy().size() > i) {
				armySlots.push_back(std::make_unique<TacticsArmySlot>(_army->getArmy()[i]->unitInformation.unitName, sf::Vector2f(armySlots.front()->getPosition().x + 60, position.y + 120)));
			}else
			{
				armySlots.push_back(std::make_unique<TacticsArmySlot>(EMPTY, sf::Vector2f(armySlots.front()->getPosition().x + 60, position.y + 120)));
			}
		}
		else
		{
			if (_army->getArmy().size() > i) {
				armySlots.push_back(std::make_unique<TacticsArmySlot>(_army->getArmy()[i]->unitInformation.unitName, position));
			}else
			{
				armySlots.push_back(std::make_unique<TacticsArmySlot>(EMPTY, sf::Vector2f(position)));
			}
		}
		
		position = armySlots.back()->getPosition() + sf::Vector2f(120,0);
	}
}

void PlayerArmy_TabMenu::UpdateUnitAmount(const std::unique_ptr<Army>& _army)
{
	for(int i =0 ; i<_army->getArmy().size(); i++)
	{
		armySlots[i]->updateUnitAmount(_army->getArmy()[i]->getStackSize());
	}
}

void PlayerArmy_TabMenu::Update()
{
}

void PlayerArmy_TabMenu::Render(const std::unique_ptr<sf::RenderWindow>& _window) const
{
	_window->draw(background);
	for(auto& slot : armySlots)
	{
		slot->render(_window);
	}
}
