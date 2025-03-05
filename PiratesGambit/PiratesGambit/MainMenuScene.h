#pragma once
#include "Scene.h"

class MainMenuScene : public Scene {
public:
    MainMenuScene();

    void handleInput(const std::unique_ptr<sf::RenderWindow>& window,sf::Event newEvent) override;
    void update(float dt) override;
    void render(const std::unique_ptr<sf::RenderWindow>& window) override;

private:
    sf::Sprite background;

    sf::Text playButton;
    sf::Text quitButton;

    void centerText(sf::Text& text, float y);
    bool isMouseOver(sf::Text& text, const std::unique_ptr<sf::RenderWindow>& window);
};


