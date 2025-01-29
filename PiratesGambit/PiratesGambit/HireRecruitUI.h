#pragma once
#include "AnimatedCharacterIcon.h"
#include"Includes.h"
#include "Structs.h"
#include"InfoBoxUI.h"

class HireRecruitUI
{
public:
	HireRecruitUI();

	void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;
	void Update(float _dt);

	void OpenUI();
	void CloseUI();

	static bool IsUIOpen(){ return uiOpen; }
private:
	static bool uiOpen;

	sf::RectangleShape background;

	sf::Sprite unit;
	AnimationState animationState;

	std::vector<std::unique_ptr<InfoBoxUI>> InformationBoxes;

	std::unique_ptr<AnimatedCharacterIcon> unitIcon;
};

