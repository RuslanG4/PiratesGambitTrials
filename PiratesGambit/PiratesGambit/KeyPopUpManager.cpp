#include "KeyPopUpManager.h"
#include"TextureManager.h"

void KeyPopUpManager::showKey(const sf::Vector2f& playerPos, std::string key)
{
    keySprite.setTexture(TextureManager::getInstance().getTexture(key));
    keySprite.setOrigin(16, 16);
    keySprite.setScale(0.5, 0.5);
    keySprite.setPosition(playerPos + offset);
    isVisible = true;
}

void KeyPopUpManager::hideKey()
{
   isVisible = false;
}

void KeyPopUpManager::Update(float dt)
{
    Animator::getInstance().AnimateKey(keySprite, state, 2, 0, dt);
}

void KeyPopUpManager::Render(const std::unique_ptr<sf::RenderWindow>& _window)
{
    if (isVisible) {
        _window->draw(keySprite);
    }
}
