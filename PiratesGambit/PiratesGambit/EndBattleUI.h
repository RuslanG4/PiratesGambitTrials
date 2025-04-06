#pragma once
#include"Includes.h"
#include"TacticsArmySlot.h"
#include"EndBattleUIButton.h"
#include"TextureManager.h"
#include"Army.h"
class EndBattleUI
{
public:
	EndBattleUI();

	void Render(const std::unique_ptr<sf::RenderWindow>& _window);

	void HandleInput(sf::Event newEvent);

	void updateUnitsLost(const std::unique_ptr<Army>& _army);
	void updateUnitsDestroyed(const std::unique_ptr<Army>& _army);

	bool isOKClicked() const { return continueButton->isClicked(); }

	void Win();
	void Lose();
private:
	void postionText();
	void initText();

	sf::Sprite background;
	sf::Sprite icon;
	sf::Text titleText;
	sf::Text outcomeText;
	sf::Text descriptionText;
	sf::Text lostUnitsText;
	sf::Text destroyedUnitsText;

	std::vector<std::unique_ptr<TacticsArmySlot>> lostUnits;
	std::vector<std::unique_ptr<TacticsArmySlot>> destroyedUnits;

	std::unique_ptr<EndBattleUIButton> continueButton;

};

