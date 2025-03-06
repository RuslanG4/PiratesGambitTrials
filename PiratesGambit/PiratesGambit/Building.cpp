#include "Building.h"

#include "Camera.h"

void Building::Render(const std::unique_ptr<sf::RenderWindow>& _window) const
{
	_window->setView(Camera::getInstance().getCamera());
	_window->draw(buildingSprite);
	//myHitbox->render(_window);
}

void Building::RenderUI(const std::unique_ptr<sf::RenderWindow>& _window) const
{
	if (buildingUI->IsMenuOpen())
	{
		_window->setView(_window->getDefaultView());
		buildingUI->Render(_window);
	}
}

void Building::Update(float _dt)
{
	buildingUI->Update(_dt);
}

void Building::Interact()
{
	if (!buildingUI->IsMenuOpen())
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
	myHitbox->setPosition(_pos);
}
