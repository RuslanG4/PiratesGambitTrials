#include "DamageCalculations.h"

int DamageCalculations::calculateHitPointsLost(const std::shared_ptr<PirateUnit>& _unit1, const std::shared_ptr<PirateUnit>& _unit2)
{
    float damageMultiplier = calcDamageMultiplier(_unit1->unitStats.attackStat, _unit2->unitStats.defenceStat);
    int baseDamage = calculateDamage(_unit1->unitStats.minDamage,_unit1->unitStats.maxDamage);

    float actualDamage = baseDamage;

    if(_unit1->unitInformation.unitType == RANGED)
    {
        actualDamage = baseDamage * rangePenalty(_unit1->getPosition(), _unit2->getPosition());
    }

    return actualDamage * _unit1->unitStats.stackSize * damageMultiplier;
}

int DamageCalculations::calculateDamage(const int& _min, const int& _max)
{
    static std::random_device rd;
    static std::mt19937 generator(rd());

    std::uniform_int_distribution<int> distribution(_min, _max);

    return distribution(generator);
}

float DamageCalculations::rangePenalty(const sf::Vector2f& _v1, const sf::Vector2f& _v2)
{
    sf::Vector2f distanceBetween = _v2 - _v1;

    if(Utility::magnitude(distanceBetween.x, distanceBetween.y) / 80 > 7)
    {
        return 0.5f;
    }
    return 1.f;
}

float DamageCalculations::calcDamageMultiplier(const int& _attack, const int& _defence)
{
    return 1.f + 0.05f * (_attack - _defence);
}
