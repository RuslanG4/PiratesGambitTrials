#include "HireRecruitUI.h"

#include "Building.h"


bool HireRecruitUI::uiOpen = false;

void HireRecruitUI::SetUpUi()
{
	background.setTexture(TextureManager::getInstance().getTexture("PLAYER_MENU_UI"));
	background.setScale(14, 10);
	background.setOrigin(48, 48);
	background.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));


	progressBar = std::make_unique<ProgressBar>(sf::Vector2f(background.getPosition().x - 150, background.getPosition().y - 50));

	costPerTroop = std::make_unique<InfoBoxUI>(4, 3);

	costPerTroop->setText("Cost Per Troop", "500");
	costPerTroop->SetIcon(TextureManager::getInstance().getTexture("COIN_ICON"));
	costPerTroop->setPosition(sf::Vector2f(background.getPosition().x - 400, background.getPosition().y));

	totalCost = std::make_unique<InfoBoxUI>(4, 3);

	totalCost->setText("Total Cost", "0");
	totalCost->SetIcon(TextureManager::getInstance().getTexture("COIN_ICON"));
	totalCost->setPosition(sf::Vector2f(background.getPosition().x + 200, background.getPosition().y));

	available = std::make_unique<InfoBoxUI>(3, 1.5);

	available->setText("Available", std::to_string(unitsLeftReference));
	available->setPosition(sf::Vector2f(background.getPosition().x + 24, background.getPosition().y));

	recruit = std::make_unique<InfoBoxUI>(3, 1.5);

	recruit->setText("Recruit", "0");
	recruit->setPosition(sf::Vector2f(background.getPosition().x - 170, background.getPosition().y));

	amountSlider = std::make_unique<Slider>(background.getPosition().x - 170, background.getPosition().y + 95, 360, 40, 1, unitsLeftReference);

	purchase = std::make_unique<IconButton>(1.5, 1.5,
		sf::Vector2f(background.getPosition().x + 60, background.getPosition().y + 200),
		TextureManager::getInstance().getTexture("MONEY_ICON"));

	cancel = std::make_unique<IconButton>(1.5, 1.5,
		sf::Vector2f(background.getPosition().x - 60, background.getPosition().y + 200),
		TextureManager::getInstance().getTexture("MONEY_ICON"));
}

void HireRecruitUI::PassUI(UnitName _type, int _unitAmount, Building& building, int _cost)
{
	unitsLeftReference = _unitAmount;
	nameOfUnitSelling = _type;
	buildingRef = &building;
	costPerUnit = _cost;
	costPerTroop->setText("Cost Per Troop", std::to_string(costPerUnit));

	if(availableUnits <=0 && building.canBuyUnits())
	{
		availableUnits = unitsLeftReference;
	}

	SetCharacter();
	amountSlider->updateMaxValue(availableUnits);
	available->setText("Available", std::to_string(availableUnits));
}

void HireRecruitUI::SetCharacter()
{
	switch (nameOfUnitSelling)
	{
	case BUCCANEER:
		unitIcon = std::make_unique<BuccaneerIcon>(sf::Vector2f(background.getPosition().x, background.getPosition().y - 200));
		break;
	case GUNNER:
		unitIcon = std::make_unique<GunnerIcon>(sf::Vector2f(background.getPosition().x, background.getPosition().y - 200));
		break;
	case HARPOONER:
		unitIcon = std::make_unique<HarpoonerIcon>(sf::Vector2f(background.getPosition().x, background.getPosition().y - 200));
		break;
	case BIRD:
		unitIcon = std::make_unique<BirdIcon>(sf::Vector2f(background.getPosition().x, background.getPosition().y - 200));
		break;
	case CANNON:
		unitIcon = std::make_unique<CannonIcon>(sf::Vector2f(background.getPosition().x, background.getPosition().y - 200));
		break;
	}
}

void HireRecruitUI::AddCharacterToPlayer() const 
{
	switch (nameOfUnitSelling)
	{
	case BUCCANEER:
		playerRef->getArmy()->addUnit(std::make_unique<Buccaneer>(amountSlider->getValue(), HUMAN_PLAYER));
		break;
	case GUNNER:
		playerRef->getArmy()->addUnit(std::make_unique<Gunner>(amountSlider->getValue(), HUMAN_PLAYER));
		break;
	case HARPOONER:
		playerRef->getArmy()->addUnit(std::make_unique<Harpooner>(amountSlider->getValue(), HUMAN_PLAYER));
		break;
	case BIRD:
		playerRef->getArmy()->addUnit(std::make_unique<BirdUnit>(amountSlider->getValue(), HUMAN_PLAYER));
		break;
	case CANNON:
		playerRef->getArmy()->addUnit(std::make_unique<CannonUnit>(amountSlider->getValue(), HUMAN_PLAYER));
		break;
	}
}

void HireRecruitUI::resetValues()
{
	totalCost->setText("Total Cost", "0");
	recruit->setText("Recruit", "0");
}

void HireRecruitUI::Render(const std::unique_ptr<sf::RenderWindow>& _window) const
{
	_window->setView(_window->getDefaultView());
	_window->draw(background);
	totalCost->Render(_window);
	costPerTroop->Render(_window);
	recruit->Render(_window);
	available->Render(_window);
	unitIcon->Render(_window);
	purchase->Render(_window);
	cancel->Render(_window);
	amountSlider->Render(_window);
	progressBar->Render(_window);
}

void HireRecruitUI::Update(float _dt)
{
	if (IsMenuOpen()) {
		unitIcon->Update(_dt);
		if (availableUnits > 0)
		{
			amountSlider->Update();
		}

		progressBar->PassProgress(buildingRef->getProgressValue());

		recruit->UpdateText(std::to_string(amountSlider->getValue()));
		totalCost->UpdateText(std::to_string(amountSlider->getValue() * costPerUnit)); 

		cancel->Update();
		if (cancel->IsTriggered() || sf::Keyboard::isKeyPressed((sf::Keyboard::Escape)))
		{
			cancel->ResetTrigger();
			costPerUnit = 0;
			CloseUI();
		}

		if (buildingRef->canBuyUnits()) {
			if (resetValue)
			{
				availableUnits = unitsLeftReference;
				resetValue = false;
				available->setText("Available", std::to_string(unitsLeftReference));
				amountSlider->updateMaxValue(availableUnits);
			}
			purchase->Update();

			if (purchase->IsTriggered() && availableUnits > 0)
			{
				auto it = std::ranges::find_if(playerRef->getInventory()->getItems(), [&](const std::unique_ptr<InventoryItem>& item) {
					return item->getItemName() == COINS;
					});

				if (it != playerRef->getInventory()->getItems().end()) {
					if ((it->get()->getStackSize() - amountSlider->getValue() * costPerUnit) >= 0) {
						std::cout << "prev stack size : " << it->get()->getStackSize() << "\n";
						it->get()->removeFromCurrentStack(amountSlider->getValue() * costPerUnit);
						std::cout << "new stack size : " << it->get()->getStackSize() << "\n";
						availableUnits -= amountSlider->getValue();
						available->setText("Available", std::to_string(availableUnits));
						AddCharacterToPlayer();
						amountSlider->updateMaxValue(availableUnits);
						purchase->ResetTrigger();

						if (availableUnits <= 0)
						{
							buildingRef->BuyUnits();
							amountSlider->ResetSlider();
							resetValues();
							resetValue = true;
						}

					}
				}
			}
		}
	}
}

void HireRecruitUI::OpenUI()
{
	uiOpen = true;
	isMenuOpen = true;
}

void HireRecruitUI::CloseUI()
{
	uiOpen = false;
	isMenuOpen = false;

	amountSlider->ResetSlider();
}
