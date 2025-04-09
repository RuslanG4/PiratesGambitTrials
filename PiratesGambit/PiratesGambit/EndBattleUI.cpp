#include "EndBattleUI.h"

EndBattleUI::EndBattleUI()
{
	icon.setTexture(TextureManager::getInstance().getTexture("CHEST_ICON"));
	icon.setScale(5, 5);

	background.setTexture(TextureManager::getInstance().getTexture("PLAYER_MENU_UI"));
	background.setOrigin(48, 48);
	background.setScale(11, 10);
	background.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	initText();

	sf::Vector2f topPosition = background.getPosition() + sf::Vector2f(-366,0);

	sf::Vector2f bottomPosition = background.getPosition() + sf::Vector2f(-366, 200);

	for (int i = 0; i < 7; i++) 
	{
		UnitStats temp;
		lostUnits.push_back(std::make_unique<TacticsArmySlot>(EMPTY,
			temp,
			sf::Vector2f(topPosition)));
		destroyedUnits.push_back(std::make_unique<TacticsArmySlot>(EMPTY,
			temp,
			sf::Vector2f(bottomPosition)));

		bottomPosition = destroyedUnits.back()->getPosition() + sf::Vector2f(120, 0);
		topPosition = lostUnits.back()->getPosition() + sf::Vector2f(120, 0);
	}
	postionText();
}

void EndBattleUI::Render(const std::unique_ptr<sf::RenderWindow>& _window)
{
	_window->draw(background);
	for (auto& slot : lostUnits)
	{
		slot->render(_window);
	}
	for (auto& slot : destroyedUnits)
	{
		slot->render(_window);
	}
	_window->draw(icon);
	_window->draw(titleText);
	_window->draw(outcomeText);
	_window->draw(descriptionText);
	_window->draw(lostUnitsText);
	_window->draw(destroyedUnitsText);
	continueButton->draw(_window);
}

void EndBattleUI::HandleInput(sf::Event newEvent)
{
	continueButton->handleEvent(newEvent);
}

void EndBattleUI::updateUnitsLost(const std::unique_ptr<Army>& _army)
{
	for (int i = 0; i < _army->getArmy().size(); i++)
	{
		lostUnits[i]->updateUnitAmount(_army->getArmy()[i]->getStackSize());
		lostUnits[i]->updateSlots(_army->getArmy()[i]->unitInformation.unitName,_army->getArmy()[i]->unitStats);
	}
}

void EndBattleUI::updateUnitsDestroyed(const std::unique_ptr<Army>& _army)
{
	for (int i = 0; i < _army->getArmy().size(); i++)
	{
		destroyedUnits[i]->updateUnitAmount(_army->getArmy()[i]->getStackSize());
		destroyedUnits[i]->updateSlots(_army->getArmy()[i]->unitInformation.unitName, _army->getArmy()[i]->unitStats);
	}
}

void EndBattleUI::Win()
{
	isWin = true;
	icon.setTexture(TextureManager::getInstance().getTexture("CHEST_ICON"));
	outcomeText.setString("Victory");
	descriptionText.setString("The enemy has been defeated \n \nYou have gained gold");
}

void EndBattleUI::Lose()
{
	isWin = false;
	icon.setTexture(TextureManager::getInstance().getTexture("SKULL_ICON"));
	outcomeText.setString("Defeat");
	descriptionText.setString("You have been defeated \n \nYou have gained gold");
}

void EndBattleUI::postionText()
{
	lostUnitsText.setPosition(lostUnits[3]->getPosition() + sf::Vector2f(-(lostUnitsText.getLocalBounds().width / 2) , -110));
	destroyedUnitsText.setPosition(destroyedUnits[3]->getPosition() + sf::Vector2f(-(destroyedUnitsText.getLocalBounds().width / 2), -110));

	outcomeText.setPosition(background.getPosition() + sf::Vector2f(-180, -270));
	titleText.setPosition(background.getPosition() + sf::Vector2f(-420, -370));

	descriptionText.setPosition(outcomeText.getPosition() + sf::Vector2f(0, 60));

	icon.setPosition(titleText.getPosition() + sf::Vector2f(25, 100));

	continueButton = std::make_unique<EndBattleUIButton>(destroyedUnits[6]->getPosition() + sf::Vector2f(-30, 110), "Ok");


}

void EndBattleUI::initText()
{
	titleText.setFont(TextureManager::getInstance().getFont("Varsity"));
	descriptionText.setFont(TextureManager::getInstance().getFont("Varsity"));
	lostUnitsText.setFont(TextureManager::getInstance().getFont("Varsity"));
	destroyedUnitsText.setFont(TextureManager::getInstance().getFont("Varsity"));
	outcomeText.setFont(TextureManager::getInstance().getFont("Varsity"));

	titleText.setCharacterSize(50);
	outcomeText.setCharacterSize(36);
	descriptionText.setCharacterSize(26);
	lostUnitsText.setCharacterSize(36);
	destroyedUnitsText.setCharacterSize(36);

	titleText.setString("Combat Results");
	outcomeText.setString("Victory");
	descriptionText.setString("The enemy has been defeated");
	lostUnitsText.setString("Lost units");
	destroyedUnitsText.setString("Destroyed units");

	titleText.setFillColor(sf::Color(212, 175, 55));
	titleText.setOutlineColor(sf::Color::Black);
	titleText.setOutlineThickness(5.f);

	outcomeText.setFillColor(sf::Color(183, 183, 183));
	destroyedUnitsText.setFillColor(sf::Color(183, 183, 183));
	lostUnitsText.setFillColor(sf::Color(183, 183, 183));
}
