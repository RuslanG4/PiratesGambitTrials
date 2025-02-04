#include "TacticsArmySlot.h"

TacticsArmySlot::TacticsArmySlot(UnitName _type, sf::Vector2f _pos, bool _mainIcon)
{
	init();
	updateSlots(_type);
	boxBorder.setScale(5, 5);
	boxBorder.setPosition(_pos);
	teamColor.setScale(5, 5);
	teamColor.setPosition(boxBorder.getPosition());
	unitSprite.setScale(8, 8);
	unitSprite.setPosition(boxBorder.getPosition());
}

TacticsArmySlot::TacticsArmySlot(UnitName _type, sf::Vector2f _pos)
{
	init();
	updateSlots(_type);
	boxBorder.setScale(2.5, 2.5);
	boxBorder.setPosition(_pos);
	teamColor.setScale(2.5, 2.5);
	teamColor.setPosition(boxBorder.getPosition());
	unitSprite.setPosition(boxBorder.getPosition());
	unitSprite.setScale(4, 4);

	unitAmountUI.setPosition(sf::Vector2f(boxBorder.getPosition().x - 32, boxBorder.getPosition().y + 32));

}

void TacticsArmySlot::init()
{
	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 32;
	rectSourceSprite.width = 32;
	rectSourceSprite.left = 0;
	rectSourceSprite.top = 0;
	unitSprite.setTextureRect(rectSourceSprite);
	unitSprite.setOrigin(16, 24);

	boxBorder.setTexture(TextureManager::getInstance().getTexture("BULKY_BORDER"));
	boxBorder.setOrigin(24, 24);

	teamColor.setSize(sf::Vector2f(48, 48));
	teamColor.setOrigin(24, 24);
	teamColor.setFillColor(sf::Color::Black);

	unitAmountUI.renderUnitAmount = false;
}

void TacticsArmySlot::updateSlots(UnitName _type)
{
	switch (_type)
	{
	case BUCCANEER:
		unitSprite.setTexture(TextureManager::getInstance().getTexture("BUCCANEER"));
		break;
	case GUNNER:
		unitSprite.setTexture(TextureManager::getInstance().getTexture("GUNNER"));
		break;
	case HARPOONER:
		unitSprite.setTexture(TextureManager::getInstance().getTexture("HARPOONER"));
		break;
	}
}

void TacticsArmySlot::updateUnitAmount(int _amount)
{
	unitAmountUI.renderUnitAmount = true;
	unitAmountUI.updateAmount(_amount);
}

void TacticsArmySlot::updateAllegianceColor(UnitAllegiance _allegiance)
{
	switch (_allegiance)
	{
	case RED_PLAYER:
		teamColor.setFillColor(sf::Color::Red);
		break;
	case BLUE_PLAYER:
		teamColor.setFillColor(sf::Color::Blue);
		break;
	case GREEN_PLAYER:
		teamColor.setFillColor(sf::Color::Green);
		break;
	case YELLOW_PLAYER:
		teamColor.setFillColor(sf::Color::Yellow);
		break;
	}
}

void TacticsArmySlot::render(const std::unique_ptr<sf::RenderWindow>& _win) const
{
	_win->draw(teamColor);
	_win->draw(boxBorder);
	_win->draw(unitSprite);
	unitAmountUI.render(_win);
}
