#include "BattleSceneTransition.h"

BattleSceneTransition::BattleSceneTransition()
    : beginTransition(false), duration(0), startRadius(0) {}

void BattleSceneTransition::startTransition(int _duration) {
    fullscreenBlack.setFillColor(sf::Color::Black);
    fullscreenBlack.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

    screenTexture.create(SCREEN_WIDTH, SCREEN_HEIGHT);

    centerCircle = std::make_unique<sf::CircleShape>(SCREEN_WIDTH / 2);
    centerCircle->setOrigin(centerCircle->getRadius(), centerCircle->getRadius());
    centerCircle->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    centerCircle->setFillColor(sf::Color::Transparent);

    startRadius = centerCircle->getRadius();
    duration = _duration;
    beginTransition = true;
    transitionTimer.restart();
}

bool BattleSceneTransition::BlackOutTransition() {
    if (!beginTransition) return false;

    float elapsedTime = transitionTimer.getElapsedTime().asSeconds();
    if (elapsedTime >= duration) {
        beginTransition = false;
        return true;
    }

    float t = elapsedTime / duration; 
    float currentRadius = startRadius * (1 - t);

    centerCircle->setRadius(currentRadius);
    centerCircle->setOrigin(currentRadius, currentRadius);

    return false;
}

void BattleSceneTransition::Update() {
    if (beginTransition) {
        BlackOutTransition();
    }
}

void BattleSceneTransition::Render(const std::unique_ptr<sf::RenderWindow>& window) {
    if (!beginTransition) return;

    window->setView(window->getDefaultView());
    
    screenTexture.clear(sf::Color::Black);
    screenTexture.draw(fullscreenBlack);

    centerCircle->setFillColor(sf::Color::Transparent);
    screenTexture.draw(*centerCircle, sf::BlendNone);
    screenTexture.display();

    sf::Sprite transitionSprite(screenTexture.getTexture());
    window->draw(transitionSprite);
}
