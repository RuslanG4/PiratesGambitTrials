#pragma once
#include "AnimatedCharacterIcon.h"
#include"Includes.h"
#include "Structs.h"
#include"InfoBoxUI.h"
#include "BuccaneerIcon.h"
#include "GunnerIcon.h"
#include "Slider.h"
#include"IconButton.h"
#include"Player.h"

class HireRecruitUI
{
public:
	HireRecruitUI(const std::shared_ptr<Player>& _playerRef, UnitName _type, int _unitAmount);

	void SetCharacter();
	void AddCharacterToPlayer() const;

	void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;
	void Update(float _dt);

	void OpenUI();
	void CloseUI();

	static bool IsUIOpen(){ return uiOpen; }
private:
	std::shared_ptr<Player> playerRef;

	UnitName nameOfUnitSelling;

	static bool uiOpen;

	int unitsLeftReference;

	sf::RectangleShape background;

	sf::Sprite unit;
	AnimationState animationState;

	std::unique_ptr<InfoBoxUI> costPerTroop;
	std::unique_ptr<InfoBoxUI> totalCost;
	std::unique_ptr<InfoBoxUI> available;
	std::unique_ptr<InfoBoxUI> recruit;

	std::unique_ptr<IconButton> purchase;
	std::unique_ptr<IconButton> cancel;

	std::unique_ptr<AnimatedCharacterIcon> unitIcon;

	std::unique_ptr<Slider> amountSlider;
};

