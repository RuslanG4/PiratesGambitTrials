#include "Building.h"

#include "Camera.h"

void Building::Render(const std::unique_ptr<sf::RenderWindow>& _window) const
{
	_window->setView(Camera::getInstance().getCamera());
	_window->draw(buildingSprite);
	popUp->Render(_window);
	//myHitbox->render(_window);
}

void Building::Update(float _dt)
{
	popUp->Update(_dt);
	if(isActive)
	{
		popUp->TogglePopUp();
	}else
	{
		popUp->ClosePopUp();
	}


	if (!isActive) {
		float elapsed = timer.getElapsedTime().asSeconds();

		if (elapsed >= 20.f) {
			isActive = true;
		}
		progress = (elapsed / 20.f);
	}

}

void Building::Interact()
{
	if (!HireRecruitUI::getInstance().IsMenuOpen())
	{
		HireRecruitUI::getInstance().OpenUI();
		HireRecruitUI::getInstance().PassUI(unitType, maxUnitAmount, *this, costPerTroop);
	}
	else
	{
		HireRecruitUI::getInstance().CloseUI();
	}
}

void Building::SetPosition(sf::Vector2f _pos)
{
	buildingSprite.setPosition(_pos);
	myHitbox->setPosition(_pos);

	sf::Vector2f pos = { _pos.x, _pos.y - buildingSprite.getLocalBounds().height };
	popUp->setPosition(pos);
}
