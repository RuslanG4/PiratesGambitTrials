#pragma once
#include "Includes.h"
#include "TextureManager.h"

/// <summary>
/// Base class for projectiles in the game.
/// Provides core functionality for movement, rendering, and firing.
/// </summary>
class Projectile
{
public:
    /// <summary>
    /// Virtual destructor to ensure proper cleanup in derived classes.
    /// </summary>
    virtual ~Projectile() = default;

    /// <summary>
    /// Pure virtual function for initialization, must be implemented in derived classes.
    /// </summary>
    virtual void init() = 0;

    /// <summary>
    /// Updates the projectile's position based on its velocity.
    /// </summary>
    void update();

    /// <summary>
    /// Renders the projectile on the given window.
    /// </summary>
    /// <param name="window">Reference to the SFML render window.</param>
    void render(const std::unique_ptr<sf::RenderWindow>& window) const;

    /// <summary>
    /// Gets the global bounds of the projectile's sprite for collision detection.
    /// </summary>
    /// <returns>FloatRect representing the bounding box.</returns>
    sf::FloatRect getBounds() const { return body.getGlobalBounds(); }

    /// <summary>
    /// Gets the current position of the projectile.
    /// </summary>
    /// <returns>Vector2f representing the position.</returns>
    sf::Vector2f getPosition() const { return position; }

    /// <summary>
    /// Gets the previous position of the projectile.
    /// </summary>
    /// <returns>Vector2f representing the previous position.</returns>
    sf::Vector2f getPrevPosition() const { return prevPosition; }

    /// <summary>
    /// Checks if the projectile is currently active.
    /// </summary>
    /// <returns>True if active, false otherwise.</returns>
    bool getIsActive() const { return isActive; }

    /// <summary>
    /// Fires the projectile from a specified position with a given velocity.
    /// </summary>
    /// <param name="_position">Starting position of the projectile.</param>
    /// <param name="_velocity">Velocity of the projectile.</param>
    void fire(sf::Vector2f _position, sf::Vector2f _velocity);

protected:
    sf::Sprite body;               // Sprite representing the projectile
    sf::Vector2f position;         // Current position of the projectile
    sf::Vector2f prevPosition;     // Previous position of the projectile
    sf::Vector2f velocity{ 0.f, 0.f };  // Velocity vector

    bool isActive{ false };        // Whether the projectile is active

    float force{ 16.f };           // Base force applied when firing the projectile
};
