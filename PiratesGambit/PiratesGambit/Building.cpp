#include "Building.h"

void Building::Render(const std::unique_ptr<sf::RenderWindow>& _window) const
{
	_window->draw(buildingSprite);
	if(buildingUI->IsUIOpen())
	{
		buildingUI->Render(_window);
	}
}

void Building::Update(float _dt)
{
	buildingUI->Update(_dt);
}

void Building::Interact()
{
	if (!buildingUI->IsUIOpen())
	{
		buildingUI->OpenUI();
	}
	else
	{
		buildingUI->CloseUI();
	}
}

void Building::SetPosition(sf::Vector2f _pos)
{
	buildingSprite.setPosition(_pos);
}
