#pragma once
#include"Includes.h"
#include"TextureManager.h"

class UnitAmount
{
public:
	UnitAmount() { init(); }

	void init();
	void render(sf::RenderWindow& _win) const;

	void centerText();

	void setPosition(sf::Vector2f _pos);
	void updateAmount(int _amount);
private:
	sf::Text amountText;
	sf::RectangleShape background;
};

