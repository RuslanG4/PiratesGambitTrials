#include "UnitAmount.h"

void UnitAmount::init()
{
	amountText.setFont(TextureManager::getInstance().getFont());
	amountText.setCharacterSize(14);

	background.setSize(sf::Vector2f(16, 16));
	background.setFillColor(sf::Color::Blue);
	background.setOutlineColor(sf::Color::White);
	background.setOutlineThickness(1);
}

void UnitAmount::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	window->draw(background);
	window->draw(amountText);
}

void UnitAmount::centerText()
{
	sf::FloatRect spriteBounds = background.getGlobalBounds();

	sf::FloatRect textBounds = amountText.getLocalBounds();

	float centerX = spriteBounds.left + (spriteBounds.width / 2.0f);
	float centerY = spriteBounds.top + (spriteBounds.height / 2.0f);

	float textOffsetX = textBounds.left + (textBounds.width / 2.0f);
	float textOffsetY = textBounds.top + (textBounds.height / 2.0f);

	amountText.setPosition(centerX - textOffsetX, centerY - textOffsetY);
}

void UnitAmount::setPosition(sf::Vector2f _pos)
{
	background.setPosition(_pos);
	centerText();
}

void UnitAmount::updateAmount(int _amount)
{
	amountText.setString(std::to_string(_amount));

	sf::FloatRect textBounds = amountText.getGlobalBounds();

	background.setSize(sf::Vector2f(textBounds.width * 2, textBounds.height * 2));

}
