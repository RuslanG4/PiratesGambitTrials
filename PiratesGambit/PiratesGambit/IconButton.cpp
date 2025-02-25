#include "IconButton.h"

IconButton::IconButton(float _scaleX, float _scaleY, sf::Vector2f _pos, const sf::Texture& _texture) : scaleX(_scaleX), scaleY(_scaleY)
{
	backGround.setTexture(TextureManager::getInstance().getTexture("ARMY_MENU_UI"));
	backGround.setScale(_scaleX, _scaleY);
	icon.setScale(_scaleX, _scaleY);

	backGround.setPosition(_pos);

	backGround.setOrigin(28, 28);

	icon.setTexture(_texture);
	icon.setOrigin(16, 16);

	icon.setPosition(_pos);

	//ScaleIcon();
}

void IconButton::Render(const std::unique_ptr<sf::RenderWindow>& _window) const
{
	_window->draw(backGround);
	_window->draw(icon);
}

void IconButton::Update()
{
	InteractionCooldown();
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getInstance().getMousePosition());

	if(backGround.getGlobalBounds().contains(mousePos))
	{
		backGround.setScale(scaleX + 0.25, scaleY + 0.25);
		icon.setScale(scaleX + 0.25, scaleY + 0.25);
		if(Mouse::getInstance().LeftClicked() && !waitPeriod)
		{
			triggered = true;
		}
	}else
	{
		backGround.setScale(scaleX, scaleY);
		icon.setScale(scaleX, scaleY);
	}
}

void IconButton::ScaleIcon()
{
	sf::Vector2f borderSize = backGround.getGlobalBounds().getSize();

	float iconMaxSize = std::min(borderSize.x * 0.8f, borderSize.y * 0.6f); // Limit the icon size
	float iconScaleFactor = iconMaxSize / std::max(icon.getTextureRect().width, icon.getTextureRect().height);
	icon.setScale(iconScaleFactor, iconScaleFactor);

	icon.setPosition(
		backGround.getPosition().x + (borderSize.x / 2 - icon.getGlobalBounds().width / 2),
		backGround.getPosition().y + (borderSize.y / 2 - icon.getGlobalBounds().height / 2)
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
