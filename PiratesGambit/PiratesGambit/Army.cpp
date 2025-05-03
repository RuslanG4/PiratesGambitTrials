#include "Army.h"

void Army::addUnit(std::shared_ptr<PirateUnit> _unit)
{
    if (!combineUnits(_unit)) {
        army.push_back(_unit);
    }
}

void Army::addUnitNoCombine(std::shared_ptr<PirateUnit> _unit)
{
    army.push_back(_unit);
}

bool Army::combineUnits(std::shared_ptr<PirateUnit> _unit)
{
    auto it = std::ranges::find_if(army, [&](const std::shared_ptr<PirateUnit>& unit) {
        return unit->unitInformation.unitName == _unit->unitInformation.unitName;
        });

    if (it != army.end()) {
        (*it)->addToCurrentStack(_unit->getStackSize());

        _unit.reset();

        return true;
    }

    return false; // No matching unit found
}

std::shared_ptr<PirateUnit> Army::removeUnit(std::shared_ptr<PirateUnit> _unit)
{
	auto it = std::ranges::find_if(army, [&](const std::shared_ptr<PirateUnit>& unit) {
		return unit->unitInformation.id == _unit->unitInformation.id;
		});
	if (it != army.end()) {
        std::shared_ptr<PirateUnit> removedUnit = *it;
        army.erase(it);
        return removedUnit;
	}
}

void Army::deleteUnit(std::shared_ptr<PirateUnit> _unit)
{
    auto it = std::ranges::find_if(army, [&](const std::shared_ptr<PirateUnit>& unit) {
        return unit->unitInformation.id == _unit->unitInformation.id;
        });
    if (it != army.end()) {
        army.erase(it);
    }
}

bool Army::isEmpty()
{
    return std::find_if(army.begin(), army.end(), [](const auto& unit) {
        return unit->unitStats.isActive;
        }) == army.end();
}
