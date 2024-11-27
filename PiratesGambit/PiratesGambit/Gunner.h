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
	void update(float _dt) override;
	void animateSprite(float _dt) override;

private:
};

