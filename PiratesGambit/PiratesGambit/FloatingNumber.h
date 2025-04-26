#pragma once
#include"Includes.h"
#include"TextureManager.h"
class FloatingNumber
{
public:
	FloatingNumber(sf::Vector2f _pos, int _value);

	void update(float deltaTime);
	void render(const std::unique_ptr<sf::RenderWindow>& _window);
	const bool isMarkedForDelete() const { return markedForDelete; }
private:
	sf::Text text;
	float lifetime;
	sf::Clock lifeTimeClock;
	bool markedForDelete = false;
};

