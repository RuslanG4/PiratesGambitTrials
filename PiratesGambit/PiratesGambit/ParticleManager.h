#pragma once
#include "BloodParticle.h"
#include "Includes.h"
#include "Particle.h"
#include "ShotParticle.h"
#include "LeafParticle.h"

/// <summary>
/// Particle factory singleton to create and manage particles in the world.
/// </summary>
class ParticleManager
{
public:
    // Delete copy constructor and assignment operator to enforce singleton pattern
    ParticleManager(const ParticleManager&) = delete;
    ParticleManager& operator=(const ParticleManager&) = delete;

    /// <summary>
    /// Gets the singleton instance of the ParticleManager.
    /// </summary>
    /// <returns>Reference to the singleton instance.</returns>
    static ParticleManager& getInstance() {
        static ParticleManager instance; // Singleton instance
        return instance;
    }

    /// <summary>
    /// Creates a blood particle at the given position.
    /// </summary>
    /// <param name="_pos">The position to spawn the blood particle.</param>
    void CreateBloodParticle(sf::Vector2f _pos)
    {
        particles.push_back(std::make_unique<BloodParticle>(_pos));
    }

    /// <summary>
    /// Creates a shooting particle effect at the given position.
    /// </summary>
    /// <param name="_pos">The position to spawn the shooting particle.</param>
    void CreateShootParticle(sf::Vector2f _pos)
    {
        particles.push_back(std::make_unique<ShotParticle>(_pos));
    }

    /// <summary>
    /// Creates a leaf particle at the given position.
    /// </summary>
    /// <param name="_pos">The position to spawn the leaf particle.</param>
    void CreateLeafParticle(sf::Vector2f _pos)
    {
        particles.push_back(std::make_unique<LeafParticle>(_pos));
    }

    /// <summary>
    /// Updates all active particles and removes any marked for deletion.
    /// </summary>
    /// <param name="_dt">Delta time for updating particle logic.</param>
    void update(float _dt) {
        for (auto& particle : particles) {
            particle->Update(_dt);
        }

        // Remove particles that are marked for deletion
        std::erase_if(particles, [](const std::unique_ptr<Particle>& particle) {
            return particle->isMarkedForDeletion();
            });
    }

    /// <summary>
    /// Renders all active particles.
    /// </summary>
    /// <param name="window">Reference to the SFML render window.</param>
    void render(const std::unique_ptr<sf::RenderWindow>& window) const {
        for (const auto& particle : particles) {
            particle->Render(window);
        }
    }

private:
    std::vector<std::unique_ptr<Particle>> particles; // Storage for active particles

    // Private constructor and destructor to enforce singleton pattern
    ParticleManager() = default;
    ~ParticleManager() = default;
};
