#pragma once
#include "PirateUnit.h"

class Gunner : public PirateUnit
{
public:
	Gunner(int _stackCount)
	{
		currentStack = _stackCount;
		unitType = UnitType::GUNNER;
		init();
	}

	void init();
	void update(float _dt) override;
	void animateSprite(float _dt) override;

private:
};

