#include "HireRecruitUI.h"

HireRecruitUI::HireRecruitUI()
{
	costPerTroop.setText("Cost Per Troop", "500");
	costPerTroop.setPosition(sf::Vector2f(300, 300));
}

void HireRecruitUI::Render(const std::unique_ptr<sf::RenderWindow>& _window) const
{
	_window->setView(_window->getDefaultView());
	costPerTroop.Render(_window);
}

void HireRecruitUI::Update()
{
}

void HireRecruitUI::OpenUI()
{
	uiOpen = true;
}

void HireRecruitUI::CloseUI()
{
	uiOpen = false;
}
