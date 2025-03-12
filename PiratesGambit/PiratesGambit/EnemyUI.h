#pragma once
#include "Includes.h"
#include "PlayerAllegiance.h"

class EnemyUI
{
public:
	EnemyUI(float width, float height, const std::unique_ptr<PlayerAllegiance>& _allegiance);

	void setPosition(sf::Vector2f _pos);

	void updateHealth(float _healthPercentage);

	void updateAllegiance(const std::unique_ptr<PlayerAllegiance>& _allegiance);

	void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;

private:
	sf::RectangleShape healthBarBackground;
	sf::RectangleShape healthBar;
	sf::CircleShape allegianceIndicator;
};

