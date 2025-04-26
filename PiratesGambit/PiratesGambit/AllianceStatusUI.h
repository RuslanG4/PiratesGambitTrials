#pragma once
#include"Includes.h"

class AllianceStatusUI
{
public:
	AllianceStatusUI(sf::Vector2f _pos);
	void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;

	void updateAllegianceLevel(const AllegianceLevel& _level);
	void PlaceIndicatorOnAllegianceBar(int _value);

	int getCostAmount() const { return costAmount; }

private:
	void ScaleAllegianceBar();

	void CenterTexts();

	sf::Text costText;
	sf::Text alligianceText;

	int costAmount;

	sf::RectangleShape background;

	std::vector<sf::CircleShape> allegianceCircles;
	sf::RectangleShape allegianceBar;
	sf::RectangleShape allegianceBarSlider;
};

