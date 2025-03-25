#pragma once
#include"Includes.h"
#include"TextureManager.h"

class UnitAmount
{
public:
	UnitAmount()
	{
		amountText.setFont(TextureManager::getInstance().getFont("Varsity"));
		amountText.setString("0");
		amountText.setCharacterSize(14);  // or appropriate size
		amountText.setFillColor(sf::Color::White);

		background.setSize(sf::Vector2f(16, 16));
		background.setFillColor(sf::Color::Blue);
		background.setOutlineColor(sf::Color::White);
		background.setOutlineThickness(1);
	}

	void render(const std::unique_ptr<sf::RenderWindow>& window) const;

	void centerText();

	void setPosition(sf::Vector2f _pos);
	void updateAmount(int _amount);

	bool renderUnitAmount = true;
private:
	sf::Text amountText;
	sf::RectangleShape background;
};

