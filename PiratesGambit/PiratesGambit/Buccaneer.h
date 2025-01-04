#pragma once
#include "PirateUnit.h"

class Buccaneer : public PirateUnit
{
public:
	Buccaneer(int _stackCount)
	{
		currentStack = _stackCount;
		unitType = UnitType::BUCCANEER;
		init();
	}

	void init();
	void animateSprite(float _dt) override;
	void update(float _dt) override;

private:
	
};

