#pragma once
#include"Includes.h"
class ProgressBar
{
public:
	ProgressBar(sf::Vector2f _pos);
	void Render(const std::unique_ptr<sf::RenderWindow>& _win) const;
	void Update();

	bool canBuyUnits() const {
		return isActive;
	}

	void BuyUnits()
	{
		isActive = false;
		timer.restart();
	}
private:
	sf::RectangleShape backgroundBar;
	sf::RectangleShape progressBar;
	sf::Clock timer;
	bool isActive = true;
};

