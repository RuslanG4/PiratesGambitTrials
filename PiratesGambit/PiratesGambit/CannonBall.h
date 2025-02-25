#pragma once
#include "Projectile.h"

/// <summary>
/// Represents a cannonball projectile, inheriting from the base Projectile class.
/// The cannonball can be fired with an initial position and optional velocity.
/// </summary>
class CannonBall : public Projectile
{
public:
    /// <summary>
    /// Constructs a CannonBall with a specified position and optional velocity.
    /// </summary>
    /// <param name="_pos">Initial position of the cannonball.</param>
    /// <param name="_vel">Initial velocity of the cannonball (default is {0,0}).</param>
    CannonBall(sf::Vector2f _pos, sf::Vector2f _vel = { 0,0 });

    /// <summary>
    /// Initializes the cannonball's properties such as sprite, texture, and physics settings.
    /// </summary>
    void init() override;
};
