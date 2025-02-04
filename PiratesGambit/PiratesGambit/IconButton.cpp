#include "IconButton.h"

IconButton::IconButton(float _width, float _height, sf::Vector2f _pos, const sf::Texture& _texture)
{
	Border = std::make_unique<sf::RectangleShape>(sf::Vector2f(_width, _height));

	Border->setFillColor(sf::Color::Transparent);
	Border->setOutlineColor(sf::Color::Black);
	Border->setOutlineThickness(3);

	Border->setPosition(_pos);

	icon.setTexture(_texture);

	ScaleIcon();
}

void IconButton::Render(const std::unique_ptr<sf::RenderWindow>& _window) const
{
	_window->draw(*Border);
	_window->draw(icon);
}

void IconButton::Update()
{
	InteractionCooldown();
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getInstance().getMousePosition());

	if(Border->getGlobalBounds().contains(mousePos))
	{
		if(Mouse::getInstance().LeftClicked() && !waitPeriod)
		{
			triggered = true;
		}
	}
}

void IconButton::ScaleIcon()
{
	sf::Vector2f borderSize = Border->getSize();

	float iconMaxSize = std::min(borderSize.x * 0.8f, borderSize.y * 0.6f); // Limit the icon size
	float iconScaleFactor = iconMaxSize / std::max(icon.getTextureRect().width, icon.getTextureRect().height);
	icon.setScale(iconScaleFactor, iconScaleFactor);

	icon.setPosition(
		Border->getPosition().x + (borderSize.x / 2 - icon.getGlobalBounds().width / 2),
		Border->getPosition().y + (borderSize.y / 2 - icon.getGlobalBounds().height / 2)
	);
}

bool IconButton::InteractionCooldown()
{
	if(waitPeriod)
	{
		if(buttonTimer.getElapsedTime().asSeconds() > 1.f)
		{
			waitPeriod = false;
			return true;
		}
	}
	return false;
}

void IconButton::ResetTrigger()
{
	triggered = false;
	waitPeriod = true;
	buttonTimer.restart();
}
