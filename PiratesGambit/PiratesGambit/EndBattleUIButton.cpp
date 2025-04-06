#include "EndBattleUIButton.h"

void EndBattleUIButton::handleEvent(const sf::Event& event)
{
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getInstance().getMousePosition());
    bool hovering = button.getGlobalBounds().contains(mousePos);

    if (hovering)
        button.setScale(1.6f, 1.1f);
    else
        button.setScale(1.5f, 1.f);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && hovering)
        clicked = true;
    else if (event.type == sf::Event::MouseButtonReleased)
        clicked = false;
}
