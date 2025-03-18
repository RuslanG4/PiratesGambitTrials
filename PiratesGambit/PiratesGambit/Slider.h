#pragma once
#include"Includes.h"
#include "Mouse.h"

class Slider
{
public:
    Slider(float x, float y, float width, float height, int minValue, int maxValue)
        : minValue(minValue), maxValue(maxValue) {

        bar.setSize(sf::Vector2f(width, height));
        bar.setFillColor(sf::Color::Black);
        bar.setPosition(x, y);

        knob.setSize(sf::Vector2f(height, height));
        knob.setFillColor(sf::Color::Green);
        knob.setPosition(x, y - (knob.getSize().y - height) / 2);
    }

    void updateMaxValue(int _newValue) { maxValue = _newValue; }

    void ResetSlider()
    {
        knob.setPosition(bar.getPosition().x, bar.getPosition().y - (knob.getSize().y - bar.getLocalBounds().height) / 2);
    }

    void Update();

    int getValue() const;

    void Render(const std::unique_ptr<sf::RenderWindow>& _win) const;

private:
    sf::RectangleShape bar;
    sf::RectangleShape knob;
    bool dragging = false;
    int minValue, maxValue;
};

