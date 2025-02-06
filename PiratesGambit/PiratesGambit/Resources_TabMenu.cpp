#include "Resources_TabMenu.h"

Resources_TabMenu::Resources_TabMenu(const std::unique_ptr<Inventory>& _playerInventory, sf::RectangleShape _pos)
{
	UpdateMenu(_playerInventory, _pos);
}

const sf::Texture& Resources_TabMenu::AllocateSprite(ItemName _ItemName)
{
	switch(_ItemName)
	{
		case COINS:
			return TextureManager::getInstance().getTexture("COIN_ICON");
			break;
		case CANNONBALLS:
			return TextureManager::getInstance().getTexture("CANNON_BALL_ICON");
			break;
		default:
			break;
	}
}

void Resources_TabMenu::UpdateMenu(const std::unique_ptr<Inventory>& _playerInventory, sf::RectangleShape _pos)
{
	playerResources.clear();

	for (auto& item : _playerInventory->getItems())
	{
		playerResources.push_back(std::make_unique<ResourceSlotUI>(AllocateSprite(item->getItemName()), item->getStackSize()));
	}

	background.setSize(sf::Vector2f(520, 180));
	background.setFillColor(sf::Color::Red);

	sf::Vector2f position = sf::Vector2f(_pos.getPosition().x + 50, _pos.getGlobalBounds().height - 460);
	background.setPosition(position);

	position = background.getPosition() + sf::Vector2f(32, 32);

	for (auto& slot : playerResources) //7 is max
	{
		slot->SetPosition(position);
		position += sf::Vector2f(0, 48);
	}
}

void Resources_TabMenu::Update()
{
}

void Resources_TabMenu::Render(const std::unique_ptr<sf::RenderWindow>& _window) const
{
	for(auto& slot : playerResources)
	{
		slot->Render(_window);
	}
}
