#pragma once
#include "Includes.h"
#include "TextureManager.h"
#include"Mouse.h"

class TacticsArmySlot
{
public:
	TacticsArmySlot(UnitName _type, sf::Vector2f _pos, bool _mainIcon);
	TacticsArmySlot(UnitName _type,sf::Vector2f _pos);

	void init();
	void updateSlots(UnitName _type);
	void updateAllegianceColor(UnitAllegiance _allegiance);
	void render(const std::unique_ptr<sf::RenderWindow>& _win) const;
	sf::Vector2f getPosition() const { return boxBorder.getPosition(); }

	sf::Sprite unitSprite;
private:
	sf::Sprite boxBorder;
	sf::RectangleShape teamColor;
	
};

