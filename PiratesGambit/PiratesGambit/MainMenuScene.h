#pragma once
#include "Scene.h"
#include "Button.h"

class MainMenuScene : public Scene {
public:
    MainMenuScene();

    void handleInput(const std::unique_ptr<sf::RenderWindow>& window,sf::Event newEvent) override;
    void update(float dt) override;
    void render(const std::unique_ptr<sf::RenderWindow>& window) override;

private:
    sf::Sprite background;

    std::unique_ptr<Button> playButton;
    std::unique_ptr<Button> ExitButton;


    void centerText(sf::Text& text, float y);
    bool isMouseOver(sf::Text& text, const std::unique_ptr<sf::RenderWindow>& window);
};


