#pragma once
#include"Includes.h"
#include"TextureManager.h"
#include"Mouse.h"

class Scene {
public:
    virtual void handleInput(const std::unique_ptr<sf::RenderWindow>& window, sf::Event newEvent) = 0;
    virtual void update(float dt) = 0;
    virtual void render(const std::unique_ptr<sf::RenderWindow>& window) = 0;
    virtual ~Scene() = default;
};

