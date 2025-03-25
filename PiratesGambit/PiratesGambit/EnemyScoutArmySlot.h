#pragma once
#include "Includes.h"
#include "PirateUnit.h"

class EnemyScoutArmySlot
{
public:
	EnemyScoutArmySlot();

	void passUnit(const std::shared_ptr<PirateUnit>& _unit);
	void setSprite(UnitInformation& _unit);
	void setText(int _amount);

	void setPosition(sf::Vector2f _pos);
	void positionText(sf::Text& _text);

	void clearSlot();

	void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;

	sf::Vector2f getPosition() const { return boxBorder.getPosition(); }
private:
	sf::RectangleShape boxBorder;
	sf::Sprite unitSprite;

	sf::Text amountText;
};

