#include "Army.h"

void Army::addUnit(std::unique_ptr<PirateUnit> _unit)
{
	army.push_back(std::move(_unit));
}

void Army::removeUnit()
{
}
