#pragma once
#include "Includes.h"
#include "TextureManager.h"
#include"Mouse.h"
#include"Army.h"
#include"TacticsArmySlot.h"

class TacticsArmyUI
{
public:
	TacticsArmyUI(const std::unique_ptr<Army>& _army);

	void extend();
	void render(sf::RenderWindow& _win) const;
private:
	std::vector<std::unique_ptr<TacticsArmySlot>> armySlots;
	std::unique_ptr<TacticsArmySlot> firstSlot;
};

