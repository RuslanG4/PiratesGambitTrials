#pragma once
#include "PirateUnit.h"
class CannonUnit :
    public PirateUnit
{
	public:
	CannonUnit(int _stackCount, UnitAllegiance _allegiance)
		: PirateUnit(RANGED, CANNON, _allegiance)
	{
		UnitStats stats = {
		8,0,true,3,_stackCount,10,6,12,15,60
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

