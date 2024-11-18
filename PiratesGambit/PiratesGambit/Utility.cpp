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

bool Utility::collisionWithPoint(sf::Vector2f point, sf::Vector2f v1, sf::Vector2f v1Size)
{
	// Get the boundaries of the rectangle
	float v1Left = v1.x;
	float v1Right = v1.x + v1Size.x;
	float v1Top = v1.y;
	float v1Bottom = v1.y + v1Size.y;

	// Check if the point is within the boundaries of the rectangle
	return point.x >= v1Left && point.x <= v1Right &&
		point.y >= v1Top && point.y <= v1Bottom;
}

bool Utility::collisionWithNode(sf::Vector2f v1, sf::Vector2f v1Size, sf::Vector2f nodePos, int nodeSize)
{
	// Get the boundaries of v1
	float v1Left = v1.x;
	float v1Right = v1.x + v1Size.x;
	float v1Top = v1.y;
	float v1Bottom = v1.y + v1Size.y;

	// Get the boundaries of the node
	float nodeLeft = nodePos.x;
	float nodeRight = nodePos.x + nodeSize;
	float nodeTop = nodePos.y;
	float nodeBottom = nodePos.y + nodeSize;

	// Check for collision
	return v1Right > nodeLeft && v1Left < nodeRight &&
		v1Bottom > nodeTop && v1Top < nodeBottom;
}
