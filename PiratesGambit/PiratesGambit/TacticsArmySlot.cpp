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
	nextTeamColor.setScale(5, 5);
	nextTeamColor.setPosition(boxBorder.getPosition());
	
	unitSprite.setPosition(boxBorder.getPosition());
	nextTeamUnitSprite.setPosition(boxBorder.getPosition());
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
	nextTeamColor.setScale(2.5, 2.5);
	nextTeamColor.setPosition(boxBorder.getPosition());


	unitSprite.setPosition(boxBorder.getPosition());
	nextTeamUnitSprite.setPosition(boxBorder.getPosition());
	
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

	nextTeamUnitSprite.setTextureRect(rectSourceSprite);
	nextTeamUnitSprite.setOrigin(16, 24);

	boxBorder.setTexture(TextureManager::getInstance().getTexture("BULKY_BORDER"));
	boxBorder.setOrigin(24, 24);
	boxBorder.setColor(sf::Color(194, 159, 106)); //border color

	teamColor.setSize(sf::Vector2f(48, 48));
	teamColor.setOrigin(24, 24);
	teamColor.setFillColor(sf::Color(84, 76, 84));

	nextTeamColor.setSize(sf::Vector2f(48, 48));
	nextTeamColor.setOrigin(24, 24);
	nextTeamColor.setFillColor(sf::Color(84, 76, 84));

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
		{
			unitSprite.setScale(4, 4);
		}
	}
	else {
		if (_type != BIRD) {
			unitSprite.setScale(4, 4);
		}
		else {
			unitSprite.setScale(2, 2);
		}

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
		teamColor.setFillColor(sf::Color(246, 232, 205));
		break;
	case RED_PLAYER:
		teamColor.setFillColor(sf::Color(207, 94, 83, 255));
		break;
	case BLUE_PLAYER:
		teamColor.setFillColor(sf::Color(107, 147, 184, 255));
		break;
	case GREEN_PLAYER:
		teamColor.setFillColor(sf::Color(112, 180, 76, 255));
		break;
	case YELLOW_PLAYER:
		teamColor.setFillColor(sf::Color(224, 180, 35, 255));
		break;
	case BLACK_PLAYER:
		teamColor.setFillColor(sf::Color(95, 115, 116, 255));
		break;
	}
}

void TacticsArmySlot::updateNextSlot(UnitName _type, UnitStats _stats)
{
	switch (_type)
	{
	case BUCCANEER:
		nextTeamUnitSprite.setTexture(TextureManager::getInstance().getTexture("BUCCANEER"));
		nextTeamUnitSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
		nextTeamUnitSprite.setOrigin(16, 24);

		occupied = true;
		break;
	case GUNNER:
		nextTeamUnitSprite.setTexture(TextureManager::getInstance().getTexture("GUNNER"));
		nextTeamUnitSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
		nextTeamUnitSprite.setOrigin(16, 24);
		occupied = true;
		break;
	case HARPOONER:
		nextTeamUnitSprite.setTexture(TextureManager::getInstance().getTexture("HARPOONER"));
		nextTeamUnitSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
		nextTeamUnitSprite.setOrigin(16, 24);
		occupied = true;
		break;
	case CANNON:
		nextTeamUnitSprite.setTexture(TextureManager::getInstance().getTexture("CANNON_UNIT"));
		nextTeamUnitSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
		nextTeamUnitSprite.setOrigin(16, 24);
		occupied = true;
		break;
	case BIRD:
		nextTeamUnitSprite.setTexture(TextureManager::getInstance().getTexture("BIRD"));
		nextTeamUnitSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
		nextTeamUnitSprite.setOrigin(32, 32);
		occupied = true;
		break;
	case EMPTY:
		occupied = false;
		break;
	}
	if (mainIcon) {
		if (_type != BIRD) {
			nextTeamUnitSprite.setScale(8, 8);
		}
		else
		{
			nextTeamUnitSprite.setScale(4, 4);
		}
	}
	else {
		if (_type != BIRD) {
			nextTeamUnitSprite.setScale(4, 4);
		}
		else {
			nextTeamUnitSprite.setScale(2, 2);
		}

	}

	//stats = _stats;
	//UnitStatsDisplay::getInstance().updateDisplay(stats);
}

void TacticsArmySlot::updateNextAllegianceColor(UnitAllegiance _allegiance)
{
	switch (_allegiance)
	{
	case HUMAN_PLAYER:
		nextTeamColor.setFillColor(sf::Color(246, 232, 205));
		break;
	case RED_PLAYER:
		nextTeamColor.setFillColor(sf::Color(207, 94, 83, 255));
		break;
	case BLUE_PLAYER:
		nextTeamColor.setFillColor(sf::Color(107, 147, 184, 255));
		break;
	case GREEN_PLAYER:
		nextTeamColor.setFillColor(sf::Color(112, 180, 76, 255));
		break;
	case YELLOW_PLAYER:
		nextTeamColor.setFillColor(sf::Color(224, 180, 35, 255));
		break;
	case BLACK_PLAYER:
		nextTeamColor.setFillColor(sf::Color(95, 115, 116, 255));
		break;
	}
}

void TacticsArmySlot::render(const std::unique_ptr<sf::RenderWindow>& _win) const
{
	//_win->draw(bgColor);
	if(fadeIn)
		_win->draw(nextTeamColor);
	_win->draw(teamColor);
	_win->draw(boxBorder);
	if(fadeIn)
		_win->draw(nextTeamUnitSprite);
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

void TacticsArmySlot::FadeIn(double dt)
{
	fadeIn = true;
	timeAliveNext += dt * 0.001f;
	float alpha = 255 * (timeAliveNext / 1.f); // Fade in over 1 second
	alpha = std::clamp(alpha, 0.0f, 255.0f);

	nextTeamUnitSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));


	sf::Color color = nextTeamColor.getFillColor();
	color.a = static_cast<sf::Uint8>(alpha);
	nextTeamColor.setFillColor(color);
}

void TacticsArmySlot::FadeInMain(double dt)
{
	fadeIn = true;
	timeAlive += dt * 0.001f;
	float alpha = 255 * (timeAlive / 1.f); // Fade in over 1 second
	alpha = std::clamp(alpha, 0.0f, 255.0f);

	unitSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));

	sf::Color color = teamColor.getFillColor();
	color.a = static_cast<sf::Uint8>(alpha);
	teamColor.setFillColor(color);
}

void TacticsArmySlot::MoveSlot(int multiplier)
{
	float moveStep = -1.75f;
	float remaining = 120.0f * multiplier - std::abs(totalMoved);

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
	timeAliveNext = 0;
	unitSprite.setColor(sf::Color(255, 255, 255, 255));
	sf::Color color = nextTeamColor.getFillColor();
	color.a = 255;
	nextTeamColor.setFillColor(color);
	fadeIn = false;
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

void TacticsArmySlot::SetMainSpriteTransparent()
{
	unitSprite.setColor(sf::Color(255, 255, 255, 0));
	nextTeamUnitSprite.setColor(sf::Color(255, 255, 255, 0));
	sf::Color color = nextTeamColor.getFillColor();
	color.a = 0;
	nextTeamColor.setFillColor(color);
	color = teamColor.getFillColor();
	color.a = 0;
	teamColor.setFillColor(color);
}

