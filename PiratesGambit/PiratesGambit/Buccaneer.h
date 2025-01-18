#pragma once
#include "PirateUnit.h"

class Buccaneer : public PirateUnit
{
public:
	Buccaneer(int _stackCount, UnitAllegiance _allegiance)
	{
		unitStats.stackSize = _stackCount;
		unitStats.initiative = 10;
		unitInformation.unitName = BUCCANEER;
		unitInformation.allegiance = _allegiance;
		unitInformation.unitType = MELEE;
		init();
	}

	void init();
	void animateSprite(float _dt) override;
	void update(float _dt) override;

private:

};

