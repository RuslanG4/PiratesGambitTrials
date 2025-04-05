#include "EnemyUI.h"

EnemyUI::EnemyUI(float width, float height)
{
    healthBarBackground.setSize(sf::Vector2f(width, height));
    healthBarBackground.setFillColor(sf::Color(50, 50, 50));
    healthBarBackground.setOutlineThickness(2);
    healthBarBackground.setOutlineColor(sf::Color::Black);

    healthBar.setSize(sf::Vector2f(width, height));
    healthBar.setFillColor(sf::Color::Green);

    allegianceIndicator.setRadius(height / 2);
    allegianceIndicator.setOutlineThickness(2);
    allegianceIndicator.setOutlineColor(sf::Color::Black);

    updateHealth(1.f);
}


void EnemyUI::setPosition(sf::Vector2f _pos)
{
	healthBarBackground.setPosition(_pos);
	healthBar.setPosition(_pos);
	allegianceIndicator.setPosition(_pos.x - allegianceIndicator.getRadius() - 10, _pos.y);
}

void EnemyUI::updateHealth(float _healthPercentage)
{
    healthBar.setSize(sf::Vector2f(healthBarBackground.getSize().x * _healthPercentage, healthBarBackground.getSize().y));
    if (_healthPercentage > 0.6f) {
        healthBar.setFillColor(sf::Color::Green);
    }
    else if (_healthPercentage > 0.3f) {
        healthBar.setFillColor(sf::Color::Yellow);
    }
    else {
        healthBar.setFillColor(sf::Color::Red);
    }
}

void EnemyUI::updateAllegiance(const PlayerAllegiance& _allegiance)
{
    if (_allegiance.isHostile()) {
        allegianceIndicator.setFillColor(sf::Color::Red);
    }
    else if (_allegiance.getAllegianceLevel() == AllegianceLevel::Neutral) {
        allegianceIndicator.setFillColor(sf::Color::Yellow);
    }
    else {
        allegianceIndicator.setFillColor(sf::Color::Green);
    }
}

void EnemyUI::Render(const std::unique_ptr<sf::RenderWindow>& _window) const
{
    _window->draw(healthBarBackground);
    _window->draw(healthBar);
    _window->draw(allegianceIndicator);
}
