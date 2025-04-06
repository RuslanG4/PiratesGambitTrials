#pragma once
#include"ResourceSlotUI.h"
#include"Inventory.h"
#include "TextureManager.h"
#include "Enums.h"

class Resources_TabMenu
{
public:
	Resources_TabMenu(const std::unique_ptr<Inventory>& _playerInventory, sf::Sprite _pos);

	const sf::Texture& AllocateSprite(ItemName _ItemName);

	void UpdateMenu(const std::unique_ptr<Inventory>& _playerInventory, sf::Sprite _pos);
	void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;
private:
	std::vector<std::unique_ptr<ResourceSlotUI>> playerResources;
};

