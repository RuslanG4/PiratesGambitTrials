#include "HireRecruitUI.h"


bool HireRecruitUI::uiOpen = false;

HireRecruitUI::HireRecruitUI(const std::shared_ptr<Player>& _playerRef, UnitName _type, int _unitAmount)
{
	unitsLeftReference = _unitAmount;
	playerRef = _playerRef;
	nameOfUnitSelling = _type;

	sf::Vector2f size = { SCREEN_WIDTH - 600, SCREEN_HEIGHT - 300 };
	background.setTexture(TextureManager::getInstance().getTexture("PLAYER_MENU_UI"));
	background.setScale(14,10);
	background.setOrigin(48,48);
	background.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

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

	recruit = std::make_unique<InfoBoxUI>(3,1.5);

	recruit->setText("Recruit", "0");
	recruit->setPosition(sf::Vector2f(background.getPosition().x  - 170, background.getPosition().y));

	amountSlider = std::make_unique<Slider>(background.getPosition().x - 170, background.getPosition().y + 95,360, 40, 1, unitsLeftReference);

	purchase = std::make_unique<IconButton>(1.5, 1.5,
		sf::Vector2f(background.getPosition().x + 60, background.getPosition().y + 200),
		TextureManager::getInstance().getTexture("MONEY_ICON"));

	cancel = std::make_unique<IconButton>(1.5, 1.5,
		sf::Vector2f(background.getPosition().x - 60, background.getPosition().y + 200),
		TextureManager::getInstance().getTexture("MONEY_ICON"));

	SetCharacter();
	
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
		unitIcon = std::make_unique<GunnerIcon>(sf::Vector2f(background.getPosition().x, background.getPosition().y - 200));
		break;
	}
}

void HireRecruitUI::AddCharacterToPlayer() const 
{
	switch (nameOfUnitSelling)
	{
	case BUCCANEER:
		playerRef->getArmy()->addUnit(std::make_unique<Buccaneer>(amountSlider->getValue(), RED_PLAYER));
		break;
	case GUNNER:
		playerRef->getArmy()->addUnit(std::make_unique<Gunner>(amountSlider->getValue(), RED_PLAYER));
		break;
	case HARPOONER:
		playerRef->getArmy()->addUnit(std::make_unique<Harpooner>(amountSlider->getValue(), RED_PLAYER));
		break;
	}
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
}

void HireRecruitUI::Update(float _dt)
{
	if (IsMenuOpen()) {
		unitIcon->Update(_dt);
		amountSlider->Update();

		recruit->UpdateText(std::to_string(amountSlider->getValue()));
		totalCost->UpdateText(std::to_string(amountSlider->getValue() * 500));

		cancel->Update();
		if (cancel->IsTriggered() || sf::Keyboard::isKeyPressed((sf::Keyboard::Escape)))
		{
			cancel->ResetTrigger();
			CloseUI();
		}

		purchase->Update();

		if (purchase->IsTriggered() && unitsLeftReference > 0)
		{
			auto it = std::ranges::find_if(playerRef->getInventory()->getItems(), [&](const std::unique_ptr<InventoryItem>& item) {
				return item->getItemName() == COINS;
				});

			if (it != playerRef->getInventory()->getItems().end()) {
				if ((it->get()->getStackSize() - amountSlider->getValue() * 500) >= 0) {
					std::cout << "prev stack size : " << it->get()->getStackSize() << "\n";
					it->get()->removeFromCurrentStack(amountSlider->getValue() * 500);
					std::cout << "new stack size : " << it->get()->getStackSize() << "\n";
					unitsLeftReference -= amountSlider->getValue();
					available->setText("Available", std::to_string(unitsLeftReference));
					AddCharacterToPlayer();
					amountSlider->updateMaxValue(unitsLeftReference);
					purchase->ResetTrigger();
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
}
