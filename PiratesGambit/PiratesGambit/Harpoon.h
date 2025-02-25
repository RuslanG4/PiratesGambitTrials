#pragma once
#include "Projectile.h"

/// <summary>
/// Represents a harpoon projectile, inheriting from the base Projectile class.
/// The harpoon can be fired with an initial position and optional velocity.
/// </summary>
class Harpoon : public Projectile
{
public:
    /// <summary>
    /// Constructs a Harpoon with a specified position and optional velocity.
    /// </summary>
    /// <param name="_pos">Initial position of the harpoon.</param>
    /// <param name="_vel">Initial velocity of the harpoon (default is {0,0}).</param>
    Harpoon(sf::Vector2f _pos, sf::Vector2f _vel = { 0,0 });

    /// <summary>
    /// Initializes the harpoon's properties such as sprite, texture, and physics settings.
    /// </summary>
    void init() override;
};
