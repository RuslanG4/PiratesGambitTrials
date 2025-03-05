#pragma once
#include "PirateUnit.h"

class Buccaneer : public PirateUnit
{
public:
	Buccaneer(int _stackCount, UnitAllegiance _allegiance)
	{
		unitInformation.unitName = BUCCANEER;
		unitInformation.allegiance = _allegiance;
		unitInformation.unitType = MELEE;

		unitAmount = std::make_unique<UnitAmount>();
		UnitStats stats = {
			10,0,true,4,_stackCount,1,2,1,2,10
		};

		unitStats = stats;
		unitBaseStats = stats;

		init();
	}

	void init();
	void animateSprite(float _dt) override;
	void update(float _dt) override;

private:

};

