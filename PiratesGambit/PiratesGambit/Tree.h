#pragma once
#include "GameObject.h"
#include "LeafParticle.h"

class Tree :
    public GameObject
{
public:
	Tree();

	void render(const std::unique_ptr<sf::RenderWindow>& window) override;

	void interact() override;

	void update(float _dt) override;

	void animateRandomizedTreeSway(float _dt);

	sf::Vector2f GetPosition() const override
	{
		return sprite.getPosition();
	}
private:
	float scale, animationTime;

	std::vector<LeafParticle> leafParticles;
};

