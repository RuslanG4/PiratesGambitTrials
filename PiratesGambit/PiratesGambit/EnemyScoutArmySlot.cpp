#include "EnemyScoutArmySlot.h"

EnemyScoutArmySlot::EnemyScoutArmySlot()
{
	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 32;
	rectSourceSprite.width = 32;
	rectSourceSprite.left = 0;
	rectSourceSprite.top = 0;
	unitSprite.setTextureRect(rectSourceSprite);
	unitSprite.setOrigin(16, 24);
	unitSprite.setScale(1.5, 1.5);

	boxBorder.setSize(sf::Vector2f(32, 32));
	boxBorder.setOutlineThickness(2.f);
	boxBorder.setOutlineColor(sf::Color(194, 159, 106));
	boxBorder.setFillColor(sf::Color(84, 76, 84));
	boxBorder.setOrigin(16, 16);

	amountText.setFont(TextureManager::getInstance().getFont("Comic"));
	amountText.setCharacterSize(12);
	amountText.setFillColor(sf::Color::White);
	amountText.setScale(1.f, 1.f);
}

void EnemyScoutArmySlot::passUnit(const std::shared_ptr<PirateUnit>& _unit)
{
	setSprite(_unit->unitInformation);
	setText(_unit->unitStats.stackSize);
}

void EnemyScoutArmySlot::setSprite(UnitInformation& _unit)
{
	switch (_unit.unitName)
	{
	case BUCCANEER:
		unitSprite.setTexture(TextureManager::getInstance().getTexture("BUCCANEER"));
		break;
	case GUNNER:
		unitSprite.setTexture(TextureManager::getInstance().getTexture("GUNNER"));
		break;
	case HARPOONER:
		unitSprite.setTexture(TextureManager::getInstance().getTexture("HARPOONER"));
		break;
	case EMPTY:
		break;
	}
}

void EnemyScoutArmySlot::setText(int _amount)
{
	if (_amount < 10)
		amountText.setString("Few");
	else if (_amount < 20)
		amountText.setString("Sev");
	else if (_amount < 40)
		amountText.setString("Lots");
	else if (_amount < 80)
		amountText.setString("Horde");

}

void EnemyScoutArmySlot::setPosition(sf::Vector2f _pos)
{
	boxBorder.setPosition(_pos);
	unitSprite.setPosition(_pos);
	positionText(amountText);
}

void EnemyScoutArmySlot::positionText(sf::Text& _text)
{
	sf::FloatRect textBounds = _text.getLocalBounds();
	sf::FloatRect boxBounds = boxBorder.getGlobalBounds();

	float padding =10.f;

	float xPos = boxBounds.left + (boxBounds.width - textBounds.width) / 2.f - textBounds.left;
	float yPos = boxBounds.top + boxBounds.height - textBounds.height - padding;

	_text.setPosition(xPos, yPos);
}

void EnemyScoutArmySlot::clearSlot()
{
	amountText.setString("");
	static sf::Texture emptyTexture;
	if (!emptyTexture.getSize().x) {
		sf::Image emptyImage;
		emptyImage.create(1, 1, sf::Color(0, 0, 0, 0));
		emptyTexture.loadFromImage(emptyImage);
	}

	unitSprite.setTexture(emptyTexture);
}

void EnemyScoutArmySlot::Render(const std::unique_ptr<sf::RenderWindow>& _window) const
{
	_window->draw(boxBorder);
	_window->draw(unitSprite);
	//_window->draw(amountText);
}
