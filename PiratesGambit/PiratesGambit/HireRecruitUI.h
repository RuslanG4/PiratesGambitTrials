#pragma once
#include "AnimatedCharacterIcon.h"
#include"Includes.h"
#include "Structs.h"
#include"InfoBoxUI.h"
#include "BuccaneerIcon.h"
#include "GunnerIcon.h"
#include "Slider.h"

class HireRecruitUI
{
public:
	HireRecruitUI(UnitName _type);

	void SetCharacter(UnitName _type);

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

	std::unique_ptr<InfoBoxUI> costPerTroop;
	std::unique_ptr<InfoBoxUI> totalCost;
	std::unique_ptr<InfoBoxUI> available;
	std::unique_ptr<InfoBoxUI> recruit;

	std::unique_ptr<AnimatedCharacterIcon> unitIcon;

	std::unique_ptr<Slider> amountSlider;
};

