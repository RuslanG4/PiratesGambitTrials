#pragma once
#include "Includes.h"
#include "PirateUnits.h"

class Army
{
public:
	Army()
	{
		
	}

	void addUnit(std::unique_ptr<PirateUnit> _unit);
	void removeUnit();

	const std::vector<std::shared_ptr<PirateUnit>>& getArmy() const { return army; }

private:
	std::vector<std::shared_ptr<PirateUnit>> army;
};

