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

	void update() override;

	void checkMousePosition();
	void RenderUI(const std::unique_ptr<sf::RenderWindow>& _window) override;

private:
	
};

