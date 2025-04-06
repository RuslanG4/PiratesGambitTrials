#pragma once
#include"Includes.h"

class BattleUIButton
{
public:
	BattleUIButton(float _scaleX, float _scaleY, sf::Vector2f _pos, const sf::Texture& _texture);
	void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;
	void Update();

	void ScaleIcon();

	bool InteractionCooldown();

	bool IsTriggered() const { return triggered; }

	void ResetTrigger();

private:
	sf::Sprite backGround;
	sf::Sprite icon;

	float scaleX, scaleY;

	sf::Clock buttonTimer;
	bool waitPeriod{ false };
	bool triggered{ false };
};

