#pragma once
#include <SFML/Graphics.hpp>
#include "PirateUnit.h"

namespace DamageCalculations
{
	int calculateHitPointsLost(const std::shared_ptr<PirateUnit>& _unit1, const std::shared_ptr<PirateUnit>& _unit2);

	int calculateDamage(const int& _min, const int& _max);

	float rangePenalty(const sf::Vector2f& _v1, const sf::Vector2f& _v2);

	float calcDamageMultiplier(const int& _attack, const int& _defence);

	UnitStats calculateDamage(UnitStats unitStats, const UnitStats& unitBaseStats, int totalDamage);
}

