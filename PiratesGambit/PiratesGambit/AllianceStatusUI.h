#pragma once
#include"Includes.h"

class AllianceStatusUI
{
public:
	AllianceStatusUI(sf::Vector2f _pos);
	void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;

	void PassValues(int _playerAllegianceValue, int _cost);

private:
	void ScaleAllegianceBar();
	void CenterTexts();

	sf::Text costText;
	sf::Text alligianceText;

	sf::RectangleShape background;

	std::vector<sf::CircleShape> allegianceCircles;
	sf::RectangleShape allegianceBar;
	sf::RectangleShape allegianceBarSlider;
};

