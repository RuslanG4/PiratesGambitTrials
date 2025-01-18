#pragma once
#include"TextureManager.h"
#include"Inventory.h"
#include"CannonBallItem.h"
#include "GameObject.h"

class Barrel : public GameObject
{
public:
	Barrel();

	void render(const std::unique_ptr<sf::RenderWindow>& window) override;
	
	void interact() override;

	void update() override;

private:
};

