#pragma once
#include "PirateUnit.h"

class Buccaneer : public PirateUnit
{
public:
	Buccaneer()
	{
		init();
	};

	void init();
	void animateSprite() override;
	void update() override;

private:
};

