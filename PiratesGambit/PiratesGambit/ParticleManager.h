#pragma once
#include "BloodParticle.h"
#include"Includes.h"
#include "Particle.h"
#include "ShotParticle.h"

class ParticleManager
{
public:
    ParticleManager(const ParticleManager&) = delete;
    ParticleManager& operator=(const ParticleManager&) = delete;

    static ParticleManager& getInstance() {
        static ParticleManager instance;
        return instance;
    }

    void CreateBloodParticle(sf::Vector2f _pos)
    {
        particles.push_back(std::make_unique<BloodParticle>(_pos));
    }

    void CreateShootParticle(sf::Vector2f _pos)
    {
        particles.push_back(std::make_unique<ShotParticle>(_pos));
    }

    void update(float _dt) {
        for (auto& particle : particles) {
            particle->Update(_dt);
        }

        std::erase_if(particles, [](const std::unique_ptr<Particle>& particle) {
            return particle->isMarkedForDeletion();
            });
    }

    void render(const std::unique_ptr<sf::RenderWindow>& window) const {
        for (const auto& particle : particles) {
            particle->Render(window);
        }
    }

private:
    std::vector<std::unique_ptr<Particle>> particles;
	ParticleManager() = default;
    ~ParticleManager() = default;

};

