#pragma once
#include "Includes.h"
#include "TextureManager.h"
#include"Mouse.h"
#include"Army.h"
#include"TacticsArmySlot.h"
#include"InitiativeSystem.h"

class TacticsArmyUI
{
public:
	TacticsArmyUI(const std::unique_ptr<Army>& _army);

	void update();
	void extend();
	void UpdateToInitiativeView();
	void UpdateToInitiativeViewAfterUnitRemoved(const std::shared_ptr<PirateUnit>& _unit);

	void startAnimation();
	void startRemoveUnitAnimation(const std::shared_ptr<PirateUnit> & _unit);

	void AnimateRemoveUnit(double dt);
	void AnimateInitiativeBar(double dt);

	void render(const std::unique_ptr<sf::RenderWindow>& _win) const;

	InitiativeSystem initiativeSystem;

	bool animateRemoveUnit = false;
	bool animateSlots = false;
	bool finsihedAnimation = true;
private:
	sf::Clock clock;
	std::vector<std::unique_ptr<TacticsArmySlot>> armySlots;
	std::unique_ptr<TacticsArmySlot> firstSlot;

	int removedUnitIndex=0;
};

