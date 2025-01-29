#include "Slider.h"

void Slider::Update()
{
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getInstance().getMousePosition());
    if (Mouse::getInstance().LeftClicked()) {
        if (knob.getGlobalBounds().contains(mousePos)) {
            dragging = true;
        }
    }
    else if (!Mouse::getInstance().LeftClicked()) {
        dragging = false;
    }
    if (dragging) {
        float leftBound = bar.getPosition().x;
        float rightBound = bar.getPosition().x + bar.getSize().x - knob.getSize().x;

        float newX = std::max(leftBound, std::min(mousePos.x, rightBound));
        knob.setPosition(newX, knob.getPosition().y);
    }
}

int Slider::getValue() const
{
    float position = knob.getPosition().x - bar.getPosition().x;
    float percentage = position / (bar.getSize().x - knob.getSize().x);
    return minValue + static_cast<int>(percentage * (maxValue - minValue));
}

void Slider::Render(const std::unique_ptr<sf::RenderWindow>& _win) const
{
    _win->draw(bar);
    _win->draw(knob);
}
