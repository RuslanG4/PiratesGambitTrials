#include "Army.h"

void Army::addUnit(std::shared_ptr<PirateUnit> _unit)
{
    if (!combineUnits(_unit)) {
        army.push_back(_unit);
    }
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

void Army::removeUnit()
{
}
