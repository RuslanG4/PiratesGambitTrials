#pragma once
#include"Includes.h"
#include"CannonBall.h"
#include"Harpoon.h"

class Harpoon;

class BulletFactory {
public:
    BulletFactory(const BulletFactory&) = delete;
    BulletFactory& operator=(const BulletFactory&) = delete;

    static BulletFactory& getInstance() {
        static BulletFactory instance;
        return instance;
    }

    void createCannonBall(const sf::Vector2f& position, const sf::Vector2f& velocity) {
        projectiles.push_back(std::make_unique<CannonBall>(position, velocity));
        projectiles.back()->init();
        projectiles.back()->fire(position, velocity);
    }

    void createHarpoon(const sf::Vector2f& position, const sf::Vector2f& velocity) {
        projectiles.push_back(std::make_unique<Harpoon>(position, velocity));
        projectiles.back()->init();
        projectiles.back()->fire(position, velocity);
    }

    void update() {
        for (auto& proj : projectiles) {
            if (proj->getIsActive()) {
                proj->update();
            }
        }
    }

    void render(const std::unique_ptr<sf::RenderWindow>& window) const {
        for (const auto& proj : projectiles) {
            if (proj->getIsActive()) {
                proj->render(window);
            }
        }
    }

    bool checkCollision(const sf::FloatRect& target) {
        for (auto it = projectiles.begin(); it != projectiles.end();) {
            if ((*it) && (*it)->getBounds().intersects(target)) {
                it = projectiles.erase(it); 
                return true;              
            }
            else {
                ++it; 
            }
        }
        return false;
    }

private:
    std::vector<std::unique_ptr<Projectile>> projectiles;

    BulletFactory() = default;
    ~BulletFactory() = default;
};

