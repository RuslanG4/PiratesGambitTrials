#include "TacticsArmyUI.h"

TacticsArmyUI::TacticsArmyUI(const std::unique_ptr<Army>& _army)
{
	firstSlot = std::make_unique<TacticsArmySlot>(EMPTY, sf::Vector2f(180, 850), 1);

	sf::Vector2f pos = firstSlot->getPosition();
	armySlots.push_back(std::make_unique<TacticsArmySlot>(_army->getArmy()[0]->unitType, sf::Vector2f(pos.x + 180, pos.y)));
	for(int i = 1; i < 7;i++)
	{
		pos = armySlots.back()->getPosition();
		if (i < _army->getArmy().size()) {
			armySlots.push_back(std::make_unique<TacticsArmySlot>(_army->getArmy()[i]->unitType, sf::Vector2f(pos.x + 120, pos.y)));
		}else
		{
			armySlots.push_back(std::make_unique<TacticsArmySlot>(EMPTY, sf::Vector2f(pos.x + 120, pos.y)));
		}
	}
}

void TacticsArmyUI::extend()
{
	for (int i = 0; i < 3; i++)
	{
		sf::Vector2f pos = armySlots.back()->getPosition();
		armySlots.push_back(std::make_unique<TacticsArmySlot>(EMPTY, sf::Vector2f(pos.x + 120, pos.y)));
	}
}

void TacticsArmyUI::render(sf::RenderWindow& _win) const
{
	for(auto& slot : armySlots)
	{
		firstSlot->render(_win);
		slot->render(_win);
	}
}
