#pragma once
#include "Includes.h"
#include "PirateUnits.h"

class Army
{
public:
	Army()
	{
		addUnit(std::move(std::make_unique<Buccaneer>()));
		addUnit(std::move(std::make_unique<Buccaneer>()));
		addUnit(std::move(std::make_unique<Buccaneer>()));
		addUnit(std::move(std::make_unique<Gunner>()));
		addUnit(std::move(std::make_unique<Gunner>()));
		addUnit(std::move(std::make_unique<Gunner>()));
	}

	void addUnit(std::unique_ptr<PirateUnit> _unit);
	void removeUnit();

	const std::vector<std::unique_ptr<PirateUnit>>& getArmy() const { return army; }

private:
	std::vector<std::unique_ptr<PirateUnit>> army;
};

