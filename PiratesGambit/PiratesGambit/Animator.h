#pragma once
#include "Includes.h"
#include "Structs.h"

/// <summary>
/// Singleton class responsible for handling animations of SFML sprites.
/// Provides various animation functions for general movement, shooting, death sequences, and particle effects.
/// </summary>
class Animator
{
public:
    /// <summary>
    /// Returns the singleton instance of the Animator.
    /// Ensures that only one instance exists throughout the program.
    /// </summary>
    /// <returns>Reference to the Animator instance.</returns>
    static Animator& getInstance() {
        static Animator instance;
        return instance;
    }

    /// <summary>
    /// Animates a sprite using a specified animation state.
    /// Updates the frame of the sprite based on time elapsed (_dt).
    /// </summary>
    /// <param name="_sprite">The sprite to animate.</param>
    /// <param name="_state">The animation state associated with the sprite.</param>
    /// <param name="_animationComplete">Flag indicating if the animation has completed.</param>
    /// <param name="_colAmt">Total number of columns in the sprite sheet.</param>
    /// <param name="_rowNum">The row number to use for the animation.</param>
    /// <param name="_dt">Delta time used for frame updates.</param>
    void AnimateSprite(sf::Sprite& _sprite, AnimationState& _state, bool& _animationComplete, int _colAmt, int _rowNum, float _dt);

    /// <summary>
    /// Animates a sprite for shooting mechanics, with an optional bullet frame trigger.
    /// </summary>
    /// <param name="_sprite">The sprite to animate.</param>
    /// <param name="_state">The animation state.</param>
    /// <param name="_animationComplete">Flag to determine if animation is complete.</param>
    /// <param name="_bulletFrame">Flag indicating when a bullet should be fired.</param>
    /// <param name="_bulletFrameNumber">Frame number at which the bullet is triggered.</param>
    /// <param name="_colAmt">Total number of columns in the sprite sheet.</param>
    /// <param name="_rowNum">The row number for the animation.</param>
    /// <param name="_dt">Delta time for frame updates.</param>
    void AnimateShoot(sf::Sprite& _sprite, AnimationState& _state, bool& _animationComplete, bool& _bulletFrame, int _bulletFrameNumber, int _colAmt, int _rowNum, float _dt);

    /// <summary>
    /// Plays a death animation sequence.
    /// </summary>
    /// <param name="_sprite">The sprite to animate.</param>
    /// <param name="_colNum">Number of columns in the sprite sheet.</param>
    /// <param name="_rowNum">The row number for the animation.</param>
    void AnimateDeath(sf::Sprite& _sprite, int _colNum, int _rowNum);

    /// <summary>
    /// Animates a particle effect, useful for effects like explosions, smoke, etc.
    /// </summary>
    /// <param name="_sprite">The particle sprite to animate.</param>
    /// <param name="_state">The animation state.</param>
    /// <param name="_animationComplete">Flag indicating if animation is complete.</param>
    /// <param name="_colNum">Number of columns in the sprite sheet.</param>
    /// <param name="_rowNum">Number of rows in the sprite sheet.</param>
    /// <param name="_width">Width of each animation frame.</param>
    /// <param name="_height">Height of each animation frame.</param>
    /// <param name="_dt">Delta time for animation updates.</param>
    void AnimateParticle(sf::Sprite& _sprite, AnimationState& _state, bool& _animationComplete, int _colNum, int _rowNum, int _width, int _height, float _dt);

    /// <summary>
    /// Deleted copy constructor to prevent multiple instances.
    /// </summary>
    Animator(Animator const&) = delete;

private:
    /// <summary>
    /// Private constructor to enforce singleton pattern.
    /// </summary>
    Animator() {}

    float animateTime{ 0 }; ///< Tracks elapsed time for animation frame updates.
    int currentFrame{ 0 };  ///< Stores the current animation frame index.
};
