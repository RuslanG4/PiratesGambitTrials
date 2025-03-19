#pragma once
#include"Includes.h"
#include "InventoryItem.h"
#include"InventorySlot.h"

class RenderableInventory {
public:
    static RenderableInventory& getInstance() {
        static RenderableInventory instance;
        return instance;
    }
    void Init();

    void passItems(const std::vector<std::unique_ptr<InventoryItem>>& _currentItems);

    void render(const std::unique_ptr<sf::RenderWindow>& window);

    std::vector<InventorySlot*> getSlots() const { return inventorySlots; }

    void OpenMenu() { isMenuOpen = true; }
    void CloseMenu() { isMenuOpen = false; }
    bool isOpen()const { return isMenuOpen; }

private:
    RenderableInventory() = default;

    RenderableInventory(const RenderableInventory&) = delete;
    RenderableInventory& operator=(const RenderableInventory&) = delete;

protected:
    sf::RectangleShape inventoryBackground;
    std::vector<InventorySlot*> inventorySlots;

    bool isMenuOpen = false;
    int _rows = 4;
    int _cols = 2;
};

