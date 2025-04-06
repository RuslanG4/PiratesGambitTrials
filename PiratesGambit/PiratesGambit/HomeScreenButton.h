#pragma once
#include "Button.h"
class HomeScreenButton :
    public Button
{
public:
    HomeScreenButton(const sf::Vector2f& position, std::string _string);
    // Inherited via Button
    void handleEvent(const sf::Event& event) override;
};

