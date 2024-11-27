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
	void animateSprite(float _dt) override;
	void update(float _dt) override;

private:
};

