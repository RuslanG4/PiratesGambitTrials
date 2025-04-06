#pragma once
#include "Button.h"
class EndBattleUIButton :
    public Button
{
public:
	EndBattleUIButton(const sf::Vector2f& position, std::string _string) : Button()
	{
		button.setScale(1.5f, 1.f);
		button.setPosition(position);
		text.setString(_string);
		text.setCharacterSize(36);
		text.setFillColor(sf::Color(220, 235, 241));
		text.setOutlineColor(sf::Color(12, 42, 61));
		text.setOutlineThickness(3.f);
		centerText(text);
	}
	// Inherited via Button
	void handleEvent(const sf::Event& event) override;
private:
	
};

