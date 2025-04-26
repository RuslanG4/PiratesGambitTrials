#pragma once
#include"Includes.h"
#include"TextureManager.h"
#include"Mouse.h"
class BattleActionButton
{
public:
	BattleActionButton(sf::Vector2f _pos, sf::Texture& _texture);
	void render(const std::unique_ptr<sf::RenderWindow>& _win) const;
	void update();
	bool UIPressed() const { return buttonPressed; }
private:
	sf::Sprite uiBorder;
	sf::Sprite attackSprite;
	bool buttonPressed{ false };
};

