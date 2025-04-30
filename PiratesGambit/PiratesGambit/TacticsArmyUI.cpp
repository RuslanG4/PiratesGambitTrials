#include "TacticsArmyUI.h"

TacticsArmyUI::TacticsArmyUI(const std::unique_ptr<Army>& _army)
{
	firstSlot = std::make_unique<TacticsArmySlot>(EMPTY,
		_army->getArmy()[0]->unitStats,
		sf::Vector2f(180, 850), 1);

	sf::Vector2f pos = firstSlot->getPosition();
	armySlots.push_back(std::make_unique<TacticsArmySlot>(_army->getArmy()[0]->unitInformation.unitName,
		_army->getArmy()[0]->unitStats, 
		sf::Vector2f(pos.x + 180, pos.y)));
	for(int i = 1; i < 7;i++)
	{
		pos = armySlots.back()->getPosition();
		if (i < _army->getArmy().size()) {
			armySlots.push_back(std::make_unique<TacticsArmySlot>(_army->getArmy()[i]->unitInformation.unitName,
				_army->getArmy()[i]->unitStats, 
				sf::Vector2f(pos.x + 120, pos.y)));
		}else
		{
			UnitStats temp;
			armySlots.push_back(std::make_unique<TacticsArmySlot>(EMPTY,
				temp,
				sf::Vector2f(pos.x + 120, pos.y)));
		}
	}
}

void TacticsArmyUI::update()
{
	for (auto& slot : armySlots)
	{
		slot->update();
	}
}

void TacticsArmyUI::extend()
{
	if (armySlots.size() >= 10)
	{
		UpdateToInitiativeView();
		return;
	}
	UnitStats stats;
	for (int i = 0; i < 3; i++)
	{
		sf::Vector2f pos = armySlots.back()->getPosition();
		armySlots.push_back(std::make_unique<TacticsArmySlot>(EMPTY,
			stats,
			sf::Vector2f(pos.x + 120, pos.y)));
	}
	UpdateToInitiativeView();
}

void TacticsArmyUI::UpdateToInitiativeView()
{
	int slotIndex = 0;
	auto turnOrder = initiativeSystem.getTurnOrder();

	for (auto& slot : armySlots) {
		if (slot == armySlots[0])
		{
			firstSlot->ResetFade();
			firstSlot->updateSlots(turnOrder[slotIndex]->unitInformation.unitName, turnOrder[slotIndex]->unitStats);
			firstSlot->updateAllegianceColor(turnOrder[slotIndex]->unitInformation.allegiance);
		}
		slot->ResetMove();
		slot->updateSlots(turnOrder[slotIndex]->unitInformation.unitName, turnOrder[slotIndex]->unitStats);
		slot->updateAllegianceColor(turnOrder[slotIndex]->unitInformation.allegiance);
		slotIndex++;
		if (slotIndex >= turnOrder.size()) {
			slotIndex = 0;
		}
	}
}

void TacticsArmyUI::startAnimation()
{
	animateSlots = true;
}

void TacticsArmyUI::AnimateInitiativeBar(double dt)
{
	if (!armySlots[0]->isStillMoving())
	{
		animateSlots = false;
		finsihedAnimation = true;
		return;
	}
	firstSlot->FadeOut(dt);
	for (auto& slot : armySlots)
	{
		slot->MoveSlot();
	}
}

void TacticsArmyUI::render(const std::unique_ptr<sf::RenderWindow>& _win) const
{
	for (auto it = armySlots.rbegin(); it != armySlots.rend(); ++it)
	{
		(*it)->render(_win);
	}
	firstSlot->render(_win);
}

