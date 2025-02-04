#pragma once
#include"Includes.h"
#include"TextureManager.h"
#include"Mouse.h"
class IconButton
{
public:
	IconButton(float _width, float _height, sf::Vector2f _pos, const sf::Texture& _texture);

	void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;
	void Update();

	void ScaleIcon();

	bool InteractionCooldown();

	bool IsTriggered() const { return triggered; }

	void ResetTrigger();

private:
	std::unique_ptr<sf::RectangleShape> Border;
	sf::Sprite icon;

	sf::Clock buttonTimer;
	bool waitPeriod{ false };
	bool triggered{false};
};

