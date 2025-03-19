#pragma once
#include"TextureManager.h"
#include"Inventory.h"
#include"CannonBallItem.h"
#include "GameObject.h"
#include"Mouse.h"

class Barrel : public GameObject
{
public:
	Barrel();

	void render(const std::unique_ptr<sf::RenderWindow>& window) override;
	
	void interact() override;

	void update(float _dt) override;

	void checkMousePosition();

	sf::Vector2f GetPosition() const override
	{
		return sprite.getPosition();
	}

private:
	
};

