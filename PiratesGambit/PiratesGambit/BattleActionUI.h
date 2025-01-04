#pragma once
#include "Includes.h"
#include "TextureManager.h"
#include"Mouse.h"

class BattleActionUI
{
public:
	BattleActionUI();
	void render(sf::RenderWindow& _win) const;
	void update();

	bool UIPressed() const { return buttonPressed; }
	void updateModeString(const std::string _text) { currentMode.setString(_text); }
private:
	sf::Sprite uiBorder;
	sf::Sprite attackSprite;

	sf::Text currentMode;

	bool buttonPressed{ false };
};

