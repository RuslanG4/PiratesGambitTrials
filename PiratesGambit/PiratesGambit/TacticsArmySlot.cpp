#include "TacticsArmySlot.h"

#include "UnitStatsDisplay.h"

TacticsArmySlot::TacticsArmySlot(UnitName _type, UnitStats _stats, sf::Vector2f _pos, bool _mainIcon)
{
	mainIcon = _mainIcon;
	stats = _stats;
	init();
	updateSlots(_type, stats);
	boxBorder.setScale(5, 5);
	boxBorder.setPosition(_pos);

	bgColor.setScale(5, 5);
	bgColor.setPosition(boxBorder.getPosition());
	teamColor.setScale(5, 5);
	teamColor.setPosition(boxBorder.getPosition());
	
	unitSprite.setPosition(boxBorder.getPosition());
}

TacticsArmySlot::TacticsArmySlot(UnitName _type, UnitStats _stats, sf::Vector2f _pos)
{
	stats = _stats;
	init();
	updateSlots(_type, stats);
	boxBorder.setScale(2.5, 2.5);
	boxBorder.setPosition(_pos);

	bgColor.setScale(2.5, 2.5);
	bgColor.setPosition(boxBorder.getPosition());
	teamColor.setScale(2.5, 2.5);
	teamColor.setPosition(boxBorder.getPosition());
	unitSprite.setPosition(boxBorder.getPosition());
	
	unitAmountUI.setPosition(sf::Vector2f(boxBorder.getPosition().x - 32, boxBorder.getPosition().y + 32));

}

void TacticsArmySlot::reset()
{
	unitAmountUI.renderUnitAmount = false;
	occupied = false;
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

	bgColor.setSize(sf::Vector2f(48, 48));
	bgColor.setOrigin(24, 24);
	bgColor.setFillColor(sf::Color(84, 76, 84));

	unitAmountUI.renderUnitAmount = false;
}

void TacticsArmySlot::updateSlots(UnitName _type, UnitStats _stats)
{
	switch (_type)
	{
	case BUCCANEER:
		unitSprite.setTexture(TextureManager::getInstance().getTexture("BUCCANEER"));
		unitSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
		unitSprite.setOrigin(16, 24);
		occupied = true;
		break;
	case GUNNER:
		unitSprite.setTexture(TextureManager::getInstance().getTexture("GUNNER"));
		unitSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
		unitSprite.setOrigin(16, 24);
		occupied = true;
		break;
	case HARPOONER:
		unitSprite.setTexture(TextureManager::getInstance().getTexture("HARPOONER"));
		unitSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
		unitSprite.setOrigin(16, 24);
		occupied = true;
		break;
	case CANNON:
		unitSprite.setTexture(TextureManager::getInstance().getTexture("CANNON_UNIT"));
		unitSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
		unitSprite.setOrigin(16, 24);
		occupied = true;
		break;
	case BIRD:
		unitSprite.setTexture(TextureManager::getInstance().getTexture("BIRD"));
		unitSprite.setTextureRect(sf::IntRect(0,0,64,64));
		unitSprite.setOrigin(32, 32);
		occupied = true;
		break;
	case EMPTY:
		occupied = false;
		break;
	}
	if (mainIcon) {
		if (_type != BIRD) {
			unitSprite.setScale(8, 8);
		}
		else
			unitSprite.setScale(4, 4);
	}
	else {
		if (_type != BIRD) {
			unitSprite.setScale(4, 4);
		}
		else
			unitSprite.setScale(2, 2);

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
	case HUMAN_PLAYER:
		teamColor.setFillColor(sf::Color::Cyan);
		break;
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
	case BLACK_PLAYER:
		teamColor.setFillColor(sf::Color::Black);
		break;
	}
}

void TacticsArmySlot::render(const std::unique_ptr<sf::RenderWindow>& _win) const
{
	//_win->draw(bgColor);
	_win->draw(teamColor);
	_win->draw(boxBorder);
	_win->draw(unitSprite);
	unitAmountUI.render(_win);
}

void TacticsArmySlot::FadeOut(double dt)
{
	timeAlive += dt * 0.001f;
	float alpha = 255 * (1.0f - (timeAlive / 1.f)); // Fade out over 0.5 seconds
	alpha = std::clamp(alpha, 0.0f, 255.0f); 

	unitSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
}

void TacticsArmySlot::MoveSlot()
{
	float moveStep = -1.75f;
	float remaining = 120.0f - std::abs(totalMoved);

	if (std::abs(moveStep) > remaining) {
		moveStep = -remaining;
		isMoving = false;     
	}

	unitSprite.move(moveStep, 0);
	teamColor.move(moveStep, 0);
	totalMoved += moveStep;
}

void TacticsArmySlot::ResetFade()
{
	timeAlive = 0;
	unitSprite.setColor(sf::Color(255, 255, 255, 255));
	isMoving = true;
}

void TacticsArmySlot::ResetMove()
{
	float offset = -totalMoved;

	unitSprite.move(offset, 0);
	teamColor.move(offset, 0);

	totalMoved = 0.0f;
	isMoving = true;
}
