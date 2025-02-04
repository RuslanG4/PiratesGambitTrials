#include "Barrel.h"

#include "BarrelInventory.h"
#include "Coins.h"

Barrel::Barrel()
{
	inventory = std::make_unique<Inventory>();
	inventory->addItem(std::make_unique<CannonBallItem>(6));
	inventory->addItem(std::make_unique<Coins>(6000));

	renderableInventory = std::make_unique<BarrelInventory>(4, 2);

	sprite.setTexture(TextureManager::getInstance().getTexture("BARREL"));
}

void Barrel::render(const std::unique_ptr<sf::RenderWindow>& window)
{
	window->draw(sprite);
	if(inventory->isInventoryOpen())
	{
		renderableInventory->render(window);
	}
}

void Barrel::interact()
{
	if(!inventory->isInventoryOpen())
	{
		inventory->openInventory();
		renderableInventory->passItems(inventory->getItems());
	}
	else
	{
		inventory->closeInventory();
	}
	
}

void Barrel::update()
{
	inventory->update();
	checkMousePosition();
}

void Barrel::checkMousePosition()
{
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getInstance().getMousePosition());
	for (auto& slot : renderableInventory->getSlots())
	{
		if (Mouse::getInstance().LeftClicked() && slot->getIsOccupied())
		{
			if (slot->getBackgroundSprite().getGlobalBounds().contains(mousePos))
			{
				std::unique_ptr<InventoryItem> item = inventory->removeItem(slot->getOccupiedBy());
			}
		}
	}
}

