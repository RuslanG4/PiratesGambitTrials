#pragma once
#include "PirateUnit.h"
#include"BulletFactory.h"

class Gunner : public PirateUnit
{
public:
	Gunner(int _stackCount, UnitAllegiance _allegiance)
	{
		unitInformation.unitName = GUNNER;
		unitInformation.allegiance = _allegiance;
		unitInformation.unitType = RANGED;

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

