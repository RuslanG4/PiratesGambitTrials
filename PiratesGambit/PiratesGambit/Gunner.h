#pragma once
#include "PirateUnit.h"

class Gunner : public PirateUnit
{
public:
	Gunner(int _stackCount, UnitAllegiance _allegiance)
	{
		unitStats.stackSize = _stackCount;
		unitStats.initiative = 8;
		unitType = UnitType::GUNNER;
		allegiance = _allegiance;
		init();
	}

	void init();
	void update(float _dt) override;
	void animateSprite(float _dt) override;

private:
};

