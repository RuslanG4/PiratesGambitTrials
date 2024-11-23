#include "Barrel.h"

Barrel::Barrel()
{
	inventory = new Inventory;
	inventory->addItem(std::move(std::make_unique<CannonBallItem>()));

	sprite.setTexture(TextureManager::getInstance().getTexture("BARREL"));
}

void Barrel::render(sf::RenderWindow& _win)
{
	_win.draw(sprite);
	if(inventory->isInventoryOpen())
	{
		inventory->getRenderableInventory()->render(_win);
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

