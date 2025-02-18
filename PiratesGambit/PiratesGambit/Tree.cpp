#include "Tree.h"

#include "BarrelInventory.h"
#include "Camera.h"
#include "TextureManager.h"

Tree::Tree()
{
	inventory = std::make_unique<Inventory>();


	renderableInventory = std::make_unique<BarrelInventory>(4, 2);
	int randO = rand() % 2;
	if(randO == 1)
	{
		sprite.setTexture(TextureManager::getInstance().getTexture("TREEA"));
		
	}else
	{
		sprite.setTexture(TextureManager::getInstance().getTexture("TREEB"));
	}
	sprite.setOrigin(16, 46);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(1.5f, 2.f); 

	float scale = dist(gen);

	sprite.setScale(scale, scale);

	myHitbox = std::make_unique<HitBox>(sf::Vector2f(12, 5));
}

void Tree::render(const std::unique_ptr<sf::RenderWindow>& window)
{
	window->draw(sprite);
	myHitbox->render(window);
}

void Tree::interact()
{
}

void Tree::update()
{
}

void Tree::RenderUI(const std::unique_ptr<sf::RenderWindow>& _window)
{
}
