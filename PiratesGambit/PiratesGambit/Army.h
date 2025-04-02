#pragma once
#include "Includes.h"
#include "PirateUnits.h"

class Army
{
public:
	Army()
	{
		
	}

	void addUnit(std::shared_ptr<PirateUnit> _unit);

	void addUnitNoCombine(std::shared_ptr<PirateUnit> _unit);

	bool combineUnits(std::shared_ptr<PirateUnit> _unit);

	void removeUnit(std::shared_ptr<PirateUnit> _unit);

	const std::vector<std::shared_ptr<PirateUnit>>& getArmy() const { return army; }

private:
	std::vector<std::shared_ptr<PirateUnit>> army;
};

