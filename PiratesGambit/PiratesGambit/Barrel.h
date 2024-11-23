#pragma once
#include"TextureManager.h"
#include"Inventory.h"
#include"CannonBallItem.h"
#include "GameObject.h"

class Barrel : public GameObject
{
public:
	Barrel();

	void render(sf::RenderWindow& _win) override;
	
	void interact() override;

	void update() override;
private:
	Inventory* inventory;
};

