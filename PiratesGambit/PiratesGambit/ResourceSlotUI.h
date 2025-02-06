#pragma once
#include"Includes.h"

class ResourceSlotUI
{
public:
	ResourceSlotUI(const sf::Texture& _icon, int _amount);

	void SetPosition(sf::Vector2f _pos);

	void CenterText();

	void Update();
	void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;
private:
	sf::Sprite iconSprite;
	sf::RectangleShape boundingBox;
	sf::RectangleShape textBoundingBox;
	sf::Text amountText;
};

