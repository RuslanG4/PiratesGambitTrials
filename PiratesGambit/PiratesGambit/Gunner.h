#pragma once
#include "PirateUnit.h"

class Gunner : public PirateUnit
{
public:
	Gunner(int _stackCount, UnitAllegiance _allegiance)
	{
		unitStats.stackSize = _stackCount;
		unitStats.initiative = 8;
		unitInformation.unitName = GUNNER;
		unitInformation.allegiance = _allegiance;
		unitInformation.unitType = RANGED;
		init();
	}

	void init();
	void update(float _dt) override;
	void animateSprite(float _dt) override;

private:
};

