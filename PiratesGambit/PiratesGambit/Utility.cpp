#include "Utility.h"

float Utility::magnitude(float x, float y)
{
	return std::sqrt(x * x + y * y);
}

sf::Vector2f Utility::unitVector2D(sf::Vector2f vec)
{
	float mag = magnitude(vec.x, vec.y);
	if (mag == 0) {
		throw std::runtime_error("Cannot normalize a zero vector.");
	}
	vec.x /= mag;
	vec.y /= mag;

	return sf::Vector2f(vec.x, vec.y);
}

sf::Vector2f Utility::truncate(sf::Vector2f v, float const max)
{
	if (magnitude(v.x, v.y) > max)
	{
		v = unitVector2D(v);
		v *= max;
	}

	return v;
}

float Utility::dotProduct(sf::Vector2f v1, sf::Vector2f v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}

bool Utility::collision(sf::Vector2f v1, sf::Vector2f v2Min, sf::Vector2f v2Max)
{
	return v1.x > v2Min.x && v1.x < v2Max.x && v1.y > v2Min.y && v1.y < v2Max.y;
}
