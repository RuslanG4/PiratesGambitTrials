#pragma once
#include"Includes.h"
class BuildingPopUp
{
public:
	BuildingPopUp();

	void Render(const std::unique_ptr<sf::RenderWindow>& _window);
	void Update(float dt);

	void setPosition(sf::Vector2f _pos);
	bool getIsActive() const { return isActive; }

	void TogglePopUp() { isActive = true; }
	void ClosePopUp() { isActive = false; }
private:
	bool isActive = true;
	float pulseTime = 0.0f;
	sf::Sprite background;
	sf::Sprite icon;
};

