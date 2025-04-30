#pragma once
#include "Includes.h"
#include "TextureManager.h"
#include"Mouse.h"
#include "PirateUnit.h"
#include "UnitAmount.h"

class TacticsArmySlot
{
public:
	TacticsArmySlot(UnitName _type, UnitStats _stats, sf::Vector2f _pos, bool _mainIcon);
	TacticsArmySlot(UnitName _type, UnitStats _stats, sf::Vector2f _pos);

	void reset();
	void update();
	void init();
	void updateSlots(UnitName _type, UnitStats _stats);
	void updateUnitAmount(int _amount);
	void updateAllegianceColor(UnitAllegiance _allegiance);
	void render(const std::unique_ptr<sf::RenderWindow>& _win) const;

	void FadeOut(double dt);
	void MoveSlot();
	void ResetFade();
	void ResetMove();

	sf::Vector2f getPosition() const { return boxBorder.getPosition(); }
	bool isStillMoving() const { return isMoving; }
	sf::Sprite unitSprite;
private:
	sf::Sprite boxBorder;
	sf::RectangleShape teamColor;
	sf::RectangleShape bgColor;

	UnitStats stats;

	bool occupied = true;
	bool mainIcon = false;

	float totalMoved = 0.0f;
	bool isMoving = true;

	float timeAlive = 0.f;

	UnitAmount unitAmountUI;
	
};

