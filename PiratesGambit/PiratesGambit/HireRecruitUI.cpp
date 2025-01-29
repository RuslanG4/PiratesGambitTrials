#include "HireRecruitUI.h"

#include "GunnerIcon.h"

bool HireRecruitUI::uiOpen = false;

HireRecruitUI::HireRecruitUI()
{
	sf::Vector2f size = { SCREEN_WIDTH - 600, SCREEN_HEIGHT - 300 };
	background.setSize(size);
	background.setOrigin(size.x / 2, size.y / 2);
	background.setFillColor(sf::Color::Red);
	background.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

	auto costPerTroop = std::make_unique<InfoBoxUI>(200, 150);

	costPerTroop->setText("Cost Per Troop", "500");
	costPerTroop->SetIcon(TextureManager::getInstance().getTexture("MONEY_ICON"));
	costPerTroop->setPosition(sf::Vector2f(background.getPosition().x - 400, background.getPosition().y));

	InformationBoxes.push_back(std::move(costPerTroop));

	auto totalCost = std::make_unique<InfoBoxUI>(200, 150);

	totalCost->setText("Total Cost", "0");
	totalCost->SetIcon(TextureManager::getInstance().getTexture("MONEY_ICON"));
	totalCost->setPosition(sf::Vector2f(background.getPosition().x + 200, background.getPosition().y));

	InformationBoxes.push_back(std::move(totalCost));

	auto available = std::make_unique<InfoBoxUI>(150,75);

	available->setText("Available", "14");
	available->setPosition(sf::Vector2f(background.getPosition().x + 30, background.getPosition().y));

	InformationBoxes.push_back(std::move(available));

	auto recruit = std::make_unique<InfoBoxUI>(150, 75);

	recruit->setText("Recruit", "0");
	recruit->setPosition(sf::Vector2f(background.getPosition().x  - 180, background.getPosition().y));

	InformationBoxes.push_back(std::move(recruit));

	unitIcon = std::make_unique<GunnerIcon>(sf::Vector2f(background.getPosition().x, background.getPosition().y - 200));
}

void HireRecruitUI::Render(const std::unique_ptr<sf::RenderWindow>& _window) const
{
	_window->setView(_window->getDefaultView());
	_window->draw(background);
	for(auto& infoBox : InformationBoxes)
	{
		infoBox->Render(_window);
	}
	unitIcon->Render(_window);
}

void HireRecruitUI::Update(float _dt)
{
	unitIcon->Update(_dt);
}

void HireRecruitUI::OpenUI()
{
	uiOpen = true;
}

void HireRecruitUI::CloseUI()
{
	uiOpen = false;
}
