#include "TacticsArmySlot.h"

TacticsArmySlot::TacticsArmySlot(UnitType _type, sf::Vector2f _pos, bool _mainIcon)
{
	init(_type);

	boxBorder.setScale(5, 5);
	boxBorder.setPosition(_pos);

	unitSprite.setScale(8, 8);
	unitSprite.setPosition(boxBorder.getPosition());
}

TacticsArmySlot::TacticsArmySlot(UnitType _type, sf::Vector2f _pos)
{
	init(_type);

	boxBorder.setScale(2.5, 2.5);
	boxBorder.setPosition(_pos);

	unitSprite.setPosition(boxBorder.getPosition());
	unitSprite.setScale(4, 4);
}

void TacticsArmySlot::init(UnitType _type)
{
	switch (_type)
	{
	case BUCCANEER:
		unitSprite.setTexture(TextureManager::getInstance().getTexture("BUCCANEER"));
		break;
	case GUNNER:
		unitSprite.setTexture(TextureManager::getInstance().getTexture("GUNNER"));
		break;
	}

	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 32;
	rectSourceSprite.width = 32;
	rectSourceSprite.left = 0;
	rectSourceSprite.top = 0;
	unitSprite.setTextureRect(rectSourceSprite);
	unitSprite.setOrigin(16, 24);

	boxBorder.setTexture(TextureManager::getInstance().getTexture("BULKY_BORDER"));
	boxBorder.setOrigin(24, 24);
}

void TacticsArmySlot::render(sf::RenderWindow& _win) const
{
	_win.draw(boxBorder);
	_win.draw(unitSprite);
}
