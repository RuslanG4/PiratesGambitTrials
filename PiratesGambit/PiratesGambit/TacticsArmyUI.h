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
	void render(const std::unique_ptr<sf::RenderWindow>& _win) const;

	InitiativeSystem initiativeSystem;
private:
	
	std::vector<std::unique_ptr<TacticsArmySlot>> armySlots;
	std::unique_ptr<TacticsArmySlot> firstSlot;
};

