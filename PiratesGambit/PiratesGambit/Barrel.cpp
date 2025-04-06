#include "Barrel.h"

#include "BarrelInventory.h"
#include "Camera.h"
#include "Coins.h"

Barrel::Barrel()
{
	inventory = std::make_unique<Inventory>();


	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> cannonBallDist(0, 4);
	int randomCannonballs = cannonBallDist(gen);

	std::uniform_int_distribution<> coinDist(150, 1000);
	int randomCoins = coinDist(gen);

	if (randomCannonballs > 0)
		inventory->addItem(std::make_unique<CannonBallItem>(randomCannonballs));

	inventory->addItem(std::make_unique<Coins>(randomCoins));

	sprite.setTexture(TextureManager::getInstance().getTexture("BARREL"));
	sprite.setScale(1.15f, 1.15f);
	sprite.setOrigin(12, 12);

	objectName = BARREL;

	myHitbox = std::make_unique<HitBox>(sf::Vector2f(8, 15));
	myHitbox->setPosition(sprite.getPosition());
}

void Barrel::render(const std::unique_ptr<sf::RenderWindow>& window)
{
	window->setView(Camera::getInstance().getCamera());
	window->draw(sprite);
	//myHitbox->render(window);
}

void Barrel::interact()
{
	if(!inventory->isInventoryOpen())
	{
		inventory->openInventory();
		RenderableInventory::getInstance().passItems(inventory->getItems());
	}
	else
	{
		inventory->closeInventory();
	}
	
}

void Barrel::update(float _dt)
{
	inventory->update();
	if (inventory->IsPersonalOpen()) {
		checkMousePosition();
	}
}

void Barrel::checkMousePosition()
{
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getInstance().getMousePosition());
	for (auto& slot : RenderableInventory::getInstance().getSlots())
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


