#include "BuildingPopUp.h"

#include "TextureManager.h"

BuildingPopUp::BuildingPopUp()
{
	background.setTexture(TextureManager::getInstance().getTexture("POP_UP"));
	background.setOrigin(48, 48);
	background.setScale(0.5, 0.5);

	icon.setTexture(TextureManager::getInstance().getTexture("MONEY_ICON"));
	icon.setOrigin(16, 16);
	icon.setScale(0.75, 0.75);
}

void BuildingPopUp::Render(const std::unique_ptr<sf::RenderWindow>& _window)
{
	if(isActive)
	{
		_window->draw(background);
		_window->draw(icon);
	}
}

void BuildingPopUp::Update(float dt)
{
	if (!isActive) return;

	pulseTime += dt; 

	float scaleFactor = 0.75f + std::sin(pulseTime * 0.001f) * 0.025f;
	float bgScaleFactor = 0.5f + std::sin(pulseTime * 0.001f) * 0.025f;

	icon.setScale(scaleFactor, scaleFactor);
	background.setScale(bgScaleFactor, bgScaleFactor);
}

void BuildingPopUp::setPosition(sf::Vector2f _pos)
{
    sf::Vector2f pos = _pos - sf::Vector2f{0, 16};
	background.setPosition(pos);
	icon.setPosition(pos);
}
