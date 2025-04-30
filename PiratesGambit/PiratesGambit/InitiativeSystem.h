#pragma once
#include "Includes.h"
#include"PirateUnits.h"
class InitiativeSystem
{
public:
    void addUnit(const std::shared_ptr<PirateUnit> unit) {
        units.push_back(unit);
        unit->unitStats.turnPoints = unit->unitStats.initiative;
    }

    int findUnitIndex(const std::shared_ptr<PirateUnit>& unit)
    {
        std::vector<std::shared_ptr<PirateUnit>> sorted = getTurnOrder();
        auto it = std::ranges::find(sorted, unit);
        if (it != sorted.end()) {
            return static_cast<int>(std::distance(sorted.begin(), it));
        }
        else {
            std::cout << "Unit not found in turn order.\n";
            return -1;
        }
    }

    void removeUnit(const std::shared_ptr<PirateUnit>& unit)
    {
        auto it = std::ranges::find(units, unit);
        if (it != units.end()) {
            units.erase(it);
            std::cout << "Unit removed successfully.\n";
        }
        else {
            std::cout << "Unit not found.\n";
        }
    }

    void ClearInitiative() {
        units.clear();
    };

    std::shared_ptr<PirateUnit> getNextUnit() {
        for (auto& unit : units) {
            if (unit->unitStats.isActive) {
                unit->unitStats.turnPoints += unit->unitStats.initiative;
            }
        }
        auto it = std::max_element(units.begin(), units.end(),
            [](const std::shared_ptr<PirateUnit>& a, const std::shared_ptr<PirateUnit>& b) {
                return a->unitStats.turnPoints < b->unitStats.turnPoints;
            });

        if (it != units.end()) {
            (*it)->unitStats.turnPoints -= 100;
            return *it;
        }

        return nullptr;
    }

    std::vector<std::shared_ptr<PirateUnit>> getTurnOrder() {
        std::vector<std::shared_ptr<PirateUnit>> sorted = units;
         std::sort(sorted.begin(), sorted.end(),
        [](const std::shared_ptr<PirateUnit>& a, const std::shared_ptr<PirateUnit>& b) {
            return a->unitStats.turnPoints > b->unitStats.turnPoints;
        });
        return sorted;
    }

private:
    std::vector<std::shared_ptr<PirateUnit>> units;
};