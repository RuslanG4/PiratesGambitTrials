#pragma once
#include "Includes.h"
#include "PirateUnit.h"

class UnitStatsDisplay
{
public:
    UnitStatsDisplay(const UnitStatsDisplay&) = delete;
    UnitStatsDisplay& operator=(const UnitStatsDisplay&) = delete;

    static UnitStatsDisplay& getInstance()
    {
        static UnitStatsDisplay instance;
        return instance;
    }

    void Render(const std::unique_ptr<sf::RenderWindow>& _win) const;
    void updateDisplay(UnitStats _stats);
    void setPosition(sf::Vector2f _pos);
    void placeText();

	void OpenMenu() { isOpen = true; }
    void CloseMenu() { isOpen = false; }

	bool isDisplayOpen() { return isOpen; }

    bool isOpen;
private:
    UnitStatsDisplay();

    sf::Sprite background;
    sf::Text speedText;
    sf::Text attackText;
    sf::Text defenceText;
    sf::Text damageRange;
    sf::Text health;
    sf::Text initiative;
    sf::Font font;
};
