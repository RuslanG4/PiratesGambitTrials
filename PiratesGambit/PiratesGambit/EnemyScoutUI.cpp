#include "EnemyScoutUI.h"

void EnemyScoutUI::clearSlots()
{
	for(auto& slot : armySlots)
	{
		slot->clearSlot();
	}
}

void EnemyScoutUI::placeMenu(sf::Vector2f _pos)
{
	sf::Vector2f backgroundPos = _pos - sf::Vector2f(0, background.getGlobalBounds().height);
	background.setPosition(backgroundPos);

	sf::Vector2f position = background.getPosition() + sf::Vector2f(42, 70);

	for (int i = 0; i < armySlots.size(); i++) //7 is max
	{
		if (i == 0)
		{
			armySlots[i]->setPosition(position);
		}
		else if (i == 4) {
			armySlots[i]->setPosition(sf::Vector2f(armySlots[0]->getPosition().x + 16 + 4, position.y + 32 + 4));
		}
		else {
			armySlots[i]->setPosition(sf::Vector2f(armySlots[i- 1]->getPosition().x + 32 + 4, position.y));
		}

		position = armySlots[i]->getPosition() + sf::Vector2f(32 + 4, 0);
	}
}

void EnemyScoutUI::Render(const std::unique_ptr<sf::RenderWindow>& _window) const
{
	if (isOpen) {
		_window->draw(background);
		for (auto& slot : armySlots)
		{
			slot->Render(_window);
		}
	}
}
