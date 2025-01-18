#include "Barrel.h"

Barrel::Barrel()
{
	inventory = std::make_unique<Inventory>();
	inventory->addItem(std::move(std::make_unique<CannonBallItem>(6)));

	sprite.setTexture(TextureManager::getInstance().getTexture("BARREL"));
}

void Barrel::render(const std::unique_ptr<sf::RenderWindow>& window)
{
	window->draw(sprite);
	if(inventory->isInventoryOpen())
	{
		inventory->getRenderableInventory()->render(window);
	}
}

void Barrel::interact()
{
	if(!inventory->isInventoryOpen())
	{
		inventory->openInventory();
	}
	else
	{
		inventory->closeInventory();
	}
	
}

void Barrel::update()
{
	inventory->update();
}

