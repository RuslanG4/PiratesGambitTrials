#pragma once
#include "PirateUnit.h"
class BirdUnit :
    public PirateUnit
{
public:
	BirdUnit(int _stackCount, UnitAllegiance _allegiance) :
		PirateUnit(MELEE, BIRD, _allegiance)
	{
		UnitStats stats = {
			14,0,true,7,_stackCount,4,2,5,7,16
		};

		unitStats = stats;
		unitBaseStats = stats;

		init();
	}

	void init();
	void animateSprite(float _dt) override;
	void update(float _dt) override;

private:

};

