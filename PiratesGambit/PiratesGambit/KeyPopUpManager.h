#pragma once
#include"Includes.h"
#include"Animator.h"
class KeyPopUpManager
{
public:
    static KeyPopUpManager& getInstance() {
        static KeyPopUpManager instance;
        return instance;
    }

    void showKey(const sf::Vector2f& playerPos, std::string key);
    void hideKey();
    void Update(float dt);
    void Render(const std::unique_ptr<sf::RenderWindow>& _window);

private:
    KeyPopUpManager() = default;

    std::map<char, sf::Texture> keyTextures;
    sf::Sprite keySprite;
    bool isVisible = false;
    sf::Vector2f offset = { 0.f, -25.f };
    AnimationState state;

    KeyPopUpManager(const KeyPopUpManager&) = delete;
    KeyPopUpManager& operator=(const KeyPopUpManager&) = delete;
};

