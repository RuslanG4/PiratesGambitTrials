#include "TacticsArmySlot.h"

#include "UnitStatsDisplay.h"

TacticsArmySlot::TacticsArmySlot(UnitName _type, UnitStats _stats, sf::Vector2f _pos, bool _mainIcon)
{
	stats = _stats;
	init();
	updateSlots(_type, stats);
	boxBorder.setScale(5, 5);
	boxBorder.setPosition(_pos);
	teamColor.setScale(5, 5);
	teamColor.setPosition(boxBorder.getPosition());
	unitSprite.setScale(8, 8);
	unitSprite.setPosition(boxBorder.getPosition());
}

TacticsArmySlot::TacticsArmySlot(UnitName _type, UnitStats _stats, sf::Vector2f _pos)
{
	stats = _stats;
	init();
	updateSlots(_type, stats);
	boxBorder.setScale(2.5, 2.5);
	boxBorder.setPosition(_pos);
	teamColor.setScale(2.5, 2.5);
	teamColor.setPosition(boxBorder.getPosition());
	unitSprite.setPosition(boxBorder.getPosition());
	unitSprite.setScale(4, 4);

	unitAmountUI.setPosition(sf::Vector2f(boxBorder.getPosition().x - 32, boxBorder.getPosition().y + 32));

}

void TacticsArmySlot::update()
{
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getInstance().getMousePosition());
	if (boxBorder.getGlobalBounds().contains(mousePos) && Mouse::getInstance().RightClicked() && occupied)
	{
		UnitStatsDisplay::getInstance().updateDisplay(stats);
		UnitStatsDisplay::getInstance().setPosition(boxBorder.getPosition());
		UnitStatsDisplay::getInstance().OpenMenu();
	}
	if(UnitStatsDisplay::getInstance().isDisplayOpen() && !Mouse::getInstance().RightClicked())
	{
		UnitStatsDisplay::getInstance().CloseMenu();
	}
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
	boxBorder.setColor(sf::Color(194, 159, 106)); //border color

	teamColor.setSize(sf::Vector2f(48, 48));
	teamColor.setOrigin(24, 24);
	teamColor.setFillColor(sf::Color(84, 76, 84));

	unitAmountUI.renderUnitAmount = false;
}

void TacticsArmySlot::updateSlots(UnitName _type, UnitStats _stats)
{
	switch (_type)
	{
	case BUCCANEER:
		unitSprite.setTexture(TextureManager::getInstance().getTexture("BUCCANEER"));
		occupied = true;
		break;
	case GUNNER:
		unitSprite.setTexture(TextureManager::getInstance().getTexture("GUNNER"));
		occupied = true;
		break;
	case HARPOONER:
		unitSprite.setTexture(TextureManager::getInstance().getTexture("HARPOONER"));
		occupied = true;
		break;
	case EMPTY:
		occupied = false;
		break;
	}
	stats = _stats;
	UnitStatsDisplay::getInstance().updateDisplay(stats);

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
