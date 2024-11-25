#pragma once
#include "PirateUnit.h"

class Gunner : public PirateUnit
{
public:
	Gunner()
	{
		init();
	};

	void init();
	void update() override;
	void animateSprite() override;

private:
};

