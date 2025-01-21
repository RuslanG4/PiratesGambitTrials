#include "EnemyMoveConditions.h"

float EnemyMoveConditions::distanceToEnemy(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	float dx = static_cast<float>(v1.x - v2.x);
	float dy = static_cast<float>(v1.y - v2.y);

	float distance = std::hypotf(dx / 80, dy / 80); //temp 80 for size

	return  distance;
}
