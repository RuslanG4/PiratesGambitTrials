#pragma once
#include "Scene.h"
#include"HomeScreenButton.h"

class MainMenuScene : public Scene {
public:
    MainMenuScene();

    void handleInput(const std::unique_ptr<sf::RenderWindow>& window,sf::Event newEvent) override;
    void update(float dt) override;
    void render(const std::unique_ptr<sf::RenderWindow>& window) override;

private:
    sf::Sprite background;

    std::unique_ptr<HomeScreenButton> playButton;
    std::unique_ptr<HomeScreenButton> ExitButton;
};


