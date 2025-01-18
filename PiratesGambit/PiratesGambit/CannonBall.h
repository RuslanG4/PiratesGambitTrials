#pragma once
#include "TextureManager.h"
#include "Utility.h"

class CannonBall 
{
public:
	CannonBall(sf::Vector2f _pos, sf::Vector2f _vel = {0,0});

	void init();
	void render(const std::unique_ptr<sf::RenderWindow>& window) const;
	void update();

	sf::FloatRect getBounds() const { return body.getGlobalBounds(); }
	sf::Vector2f getPosition() const { return position; }
	bool getIsActive() const { return isActive; }

	void fire(sf::Vector2f _position, sf::Vector2f _velocity);
	
private:
	sf::Sprite body;
	sf::Vector2f position;
	sf::Vector2f velocity{ 0.f,0.f };

	bool isActive{ false };

	float force{ 8.5 };
};

