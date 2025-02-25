#pragma once
#include "GameObject.h"

class Tree :
    public GameObject
{
public:
	Tree();

	void render(const std::unique_ptr<sf::RenderWindow>& window) override;

	void interact() override;

	void update(float _dt) override;

	void animateRandomizedTreeSway(float _dt);

	void RenderUI(const std::unique_ptr<sf::RenderWindow>& _window) override;

	sf::Vector2f GetPosition() const override
	{
		return sprite.getPosition();
	}
private:
	float scale, animationTime;
};

