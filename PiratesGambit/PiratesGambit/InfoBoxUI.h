#pragma once
#include"Includes.h"
#include"TextureManager.h"

class InfoBoxUI
{
public:
	InfoBoxUI(float _width, float _height);

	void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;
	void Update();

	void setText(const std::string& top, const std::string& bottom);
	void SetIcon(const sf::Texture& _texture);
	void setPosition(sf::Vector2f _pos);

	void RemoveIcon();

	void UpdateLayout();

private:
	std::unique_ptr<sf::RectangleShape> Border;

	sf::Sprite icon;

	sf::Text topText;
	sf::Text bottomText;

	float width, height;

	bool hasIcon{ false };
};

