#pragma once
#include "Includes.h"
#include "TextureManager.h"
#include"Mouse.h"
#include"BattleActionButton.h"

class BattleActionUI
{
public:
	BattleActionUI();
	void render(const std::unique_ptr<sf::RenderWindow>& _win) const;
	void update();

	bool UIAttackPressed() const { return attackButton->UIPressed(); }
	bool UIWaitPressed() const { return waitButton->UIPressed(); }
	void updateModeString(const std::string _text) { currentMode.setString(_text); }
private:
	sf::Text currentMode;

	std::unique_ptr<BattleActionButton> attackButton;
	std::unique_ptr<BattleActionButton> waitButton;

};

