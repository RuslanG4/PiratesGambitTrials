#pragma once
#include "Army.h"
#include "Includes.h"
#include"EnemyScoutArmySlot.h"

class EnemyScoutUI
{
public:
	EnemyScoutUI(const EnemyScoutUI&) = delete;
	EnemyScoutUI& operator=(const EnemyScoutUI&) = delete;

	static EnemyScoutUI& getInstance()
	{
		static EnemyScoutUI instance;
		return instance;
	}


	void passArmy(const std::unique_ptr<Army>& _army, const std::string& _pirateName)
	{
		pirateName.setString(_pirateName);
		difficulty.setString("Challenging");
		clearSlots();
		PositionText();
		for (int i = 0; i < _army->getArmy().size(); i++)
		{
			armySlots[i]->passUnit(_army->getArmy()[i]);
		}
	}

	void clearSlots();

	void placeMenu(sf::Vector2f _pos);

	void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;

	void OpenMenu() { isOpen = true; }
	void CloseMenu() { isOpen = false; }

	bool isDisplayOpen() const { return isOpen; }

	float getWidth() const { return background.getGlobalBounds().width; }
	float getHeight() const { return background.getGlobalBounds().height; }


private:
	EnemyScoutUI()
	{
		for (int i = 0; i < 7; i++)
		{
			armySlots.push_back(std::make_unique<EnemyScoutArmySlot>());
		}
		background.setTexture(TextureManager::getInstance().getTexture("PLAYER_MENU_UI"));
		background.setScale(2, 2);
		isOpen = false;

		pirateName.setFont(TextureManager::getInstance().getFont("Varsity"));
		pirateName.setCharacterSize(20);
		pirateName.setFillColor(sf::Color::White);

		difficulty.setFont(TextureManager::getInstance().getFont("Varsity"));
		difficulty.setCharacterSize(20);
		difficulty.setFillColor(sf::Color::White);
	}

	void PositionText();

	std::vector<std::unique_ptr<EnemyScoutArmySlot>> armySlots;
	sf::Sprite background;

	sf::Text pirateName;
	sf::Text difficulty;

	bool isOpen;
};

