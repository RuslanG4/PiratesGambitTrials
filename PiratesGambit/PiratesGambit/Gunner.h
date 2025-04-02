#pragma once
#include "PirateUnit.h"

class Gunner : public PirateUnit
{
public:
	Gunner(int _stackCount, UnitAllegiance _allegiance)
		: PirateUnit(RANGED, GUNNER, _allegiance)
	{
		UnitStats stats = {
		9,0,true,4,_stackCount,4,3,2,4,10
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

