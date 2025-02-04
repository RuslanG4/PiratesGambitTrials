#pragma once
#include "Includes.h"
#include"TextureManager.h"

class BattleSceneTransition
{
public:
	BattleSceneTransition();

	void Update();
	void Render(const std::unique_ptr<sf::RenderWindow>& window);

	void startTransition(int _duration);

	bool IsTransitionActive() const { return beginTransition; }

	bool BlackOutTransition();
private:
	std::unique_ptr<sf::CircleShape> centerCircle;
	sf::RectangleShape fullscreenBlack;

	sf::RenderTexture screenTexture;

	sf::Clock transitionTimer;

	int duration;
	bool beginTransition{false};

	float startRadius;


};

