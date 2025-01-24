#pragma once
#include "PirateUnit.h"

class Harpooner : public PirateUnit
{
public:
	Harpooner(int _stackCount, UnitAllegiance _allegiance)
	{
		unitInformation.unitName = HARPOONER;
		unitInformation.allegiance = _allegiance;
		unitInformation.unitType = RANGED;

		UnitStats stats = {
		10,0,true,3,_stackCount,9,7,7,12,42
		};

		unitStats = stats;
		unitBaseStats = stats;

		init();
	}

	void init();
	void update(float _dt) override;
	void animateSprite(float _dt) override;

private:
	bool shootBullet = false;

	sf::Vector2f bulletDirection;
};

