#pragma once
#include"ResourceSlotUI.h"
#include"Inventory.h"
#include "TextureManager.h"
#include "Enums.h"

class Resources_TabMenu
{
public:
	Resources_TabMenu(const std::unique_ptr<Inventory>& _playerInventory, sf::RectangleShape _pos);

	const sf::Texture& AllocateSprite(ItemName _ItemName);

	void UpdateMenu(const std::unique_ptr<Inventory>& _playerInventory, sf::RectangleShape _pos);
	void Update();
	void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;
private:
	sf::RectangleShape background;
	std::vector<std::unique_ptr<ResourceSlotUI>> playerResources;
};

