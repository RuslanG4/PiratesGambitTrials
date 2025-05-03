#pragma once
#include "Includes.h"
#include "PirateUnits.h"

class Army
{
public:
	Army()
	{
		
	}

	void clearArmy()
	{
		army.clear();
	}

	void addUnit(std::shared_ptr<PirateUnit> _unit);

	void addUnitNoCombine(std::shared_ptr<PirateUnit> _unit);

	bool combineUnits(std::shared_ptr<PirateUnit> _unit);

	std::shared_ptr<PirateUnit> removeUnit(std::shared_ptr<PirateUnit> _unit);

	void deleteUnit(std::shared_ptr<PirateUnit> _unit);

	bool isEmpty();

	const std::vector<std::shared_ptr<PirateUnit>>& getArmy() const { return army; }

private:
	std::vector<std::shared_ptr<PirateUnit>> army;
};

