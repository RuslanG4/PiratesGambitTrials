#pragma once
#include"Includes.h"
#include "TextureManager.h"

class Projectile
{
public:
	virtual ~Projectile() = default;

	virtual void init() = 0;
	void update();
	void render(const std::unique_ptr<sf::RenderWindow>& window) const;

	sf::FloatRect getBounds() const { return body.getGlobalBounds(); }
	sf::Vector2f getPosition() const { return position; }
	sf::Vector2f getPrevPosition() const { return prevPosition; }
	bool getIsActive() const { return isActive; }

	void fire(sf::Vector2f _position, sf::Vector2f _velocity);
protected:
	sf::Sprite body;
	sf::Vector2f position;
	sf::Vector2f prevPosition;
	sf::Vector2f velocity{ 0.f,0.f };

	bool isActive{ false };

	float force{ 16.f };
};

