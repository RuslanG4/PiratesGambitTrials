#pragma once
#include"Includes.h"
#include"Animator.h"
#include "TextureManager.h"


/// <summary>
/// Base Class for game particles
/// </summary>
class Particle
{
public:
	virtual ~Particle() = default;
	/// <summary>
	/// Update function for particles
	/// </summary>
	/// <param name="_dt">Delta time</param>
	virtual void Update(float _dt) = 0;
	/// <summary>
	/// Draws particles to screen
	/// </summary>
	/// <param name="window">Render Window</param>
	void Render(const std::unique_ptr<sf::RenderWindow>& window) const;
	/// <summary>
	/// Marker for when to destroy particle
	/// </summary>
	/// <returns></returns>
	bool isMarkedForDeletion() const { return animationFinish; }
protected:
	sf::Sprite particleSpriteSheet;
	AnimationState animationState;
	bool animationFinish{false};
	
};

