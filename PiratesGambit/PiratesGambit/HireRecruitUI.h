#pragma once
#include"Includes.h"
#include "Structs.h"
#include"InfoBoxUI.h"

class HireRecruitUI
{
public:
	HireRecruitUI();

	void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;
	void Update();

	void OpenUI();
	void CloseUI();

	bool IsUIOpen() const { return uiOpen; }
private:
	bool uiOpen{false};

	sf::Sprite unit;
	AnimationState animationState;

	InfoBoxUI costPerTroop;
};

