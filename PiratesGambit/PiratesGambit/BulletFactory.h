#pragma once
#include"Includes.h"
#include"CannonBall.h"

class BulletFactory {
public:
    BulletFactory(const BulletFactory&) = delete;
    BulletFactory& operator=(const BulletFactory&) = delete;

    static BulletFactory& getInstance() {
        static BulletFactory instance;
        return instance;
    }

    void createCannonBall(const sf::Vector2f& position, const sf::Vector2f& velocity) {
        cannonBalls.emplace_back(position, velocity);
        cannonBalls.back().init();
        cannonBalls.back().fire(position, velocity);
    }

    void update() {
        for (auto& ball : cannonBalls) {
            if (ball.getIsActive()) {
                ball.update();
            }
        }
    }

    void render(const std::unique_ptr<sf::RenderWindow>& window) const {
        for (const auto& ball : cannonBalls) {
            if (ball.getIsActive()) {
                ball.render(window);
            }
        }
    }

    bool checkCollision(const sf::FloatRect& target) {
        for (auto it = cannonBalls.begin(); it != cannonBalls.end();) {
            if (it->getIsActive() && it->getBounds().intersects(target)) {
                it = cannonBalls.erase(it); 
                return true; 
            }
            else {
                ++it; 
            }
        }
        return false;
    }

private:
    std::vector<CannonBall> cannonBalls;

    BulletFactory() = default;
    ~BulletFactory() = default;
};

