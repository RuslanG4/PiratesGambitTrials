#pragma once
#include "Includes.h"
#include "TextureManager.h"
#include"Mouse.h"

class TacticsArmySlot
{
public:
	TacticsArmySlot(UnitType _type, sf::Vector2f _pos, bool _mainIcon);
	TacticsArmySlot(UnitType _type,sf::Vector2f _pos);

	void init(UnitType _type);
	void render(sf::RenderWindow& _win) const;
	sf::Vector2f getPosition() const { return boxBorder.getPosition(); }

	sf::Sprite unitSprite;
private:
	sf::Sprite boxBorder;
	
};

