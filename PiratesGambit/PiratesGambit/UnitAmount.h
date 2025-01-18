#pragma once
#include"Includes.h"
#include"TextureManager.h"

class UnitAmount
{
public:
	UnitAmount() { init(); }

	void init();
	void render(const std::unique_ptr<sf::RenderWindow>& window) const;

	void centerText();

	void setPosition(sf::Vector2f _pos);
	void updateAmount(int _amount);
private:
	sf::Text amountText;
	sf::RectangleShape background;
};

