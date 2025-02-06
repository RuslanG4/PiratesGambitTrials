#include "ResourceSlotUI.h"

#include "TextureManager.h"

ResourceSlotUI::ResourceSlotUI(const sf::Texture& _icon, int _amount)
{
	boundingBox.setSize(sf::Vector2f(96, 32));
	boundingBox.setOutlineColor(sf::Color::Black);
	boundingBox.setFillColor(sf::Color::Transparent);
	boundingBox.setOutlineThickness(3);

	textBoundingBox.setSize(sf::Vector2f(62, 32));
	textBoundingBox.setOutlineColor(sf::Color::Black);
	textBoundingBox.setFillColor(sf::Color::Transparent);
	textBoundingBox.setOutlineThickness(3);

	amountText.setFont(TextureManager::getInstance().getFont());
	amountText.setCharacterSize(32U);
	amountText.setString(std::to_string(_amount));

	iconSprite.setTexture(_icon);
}

void ResourceSlotUI::SetPosition(sf::Vector2f _pos)
{
	boundingBox.setPosition(_pos);
	iconSprite.setPosition(boundingBox.getPosition());
	textBoundingBox.setPosition(sf::Vector2f(iconSprite.getGlobalBounds().left + iconSprite.getGlobalBounds().width, boundingBox.getPosition().y));
	CenterText();
}

void ResourceSlotUI::CenterText()
{
	sf::FloatRect spriteBounds = textBoundingBox.getGlobalBounds();

	sf::FloatRect textBounds = amountText.getLocalBounds();

	float centerX = spriteBounds.left + (spriteBounds.width / 2.0f);
	float centerY = spriteBounds.top + (spriteBounds.height / 2.0f);

	float textOffsetX = textBounds.left + (textBounds.width / 2.0f);
	float textOffsetY = textBounds.top + (textBounds.height / 2.0f);

	amountText.setPosition(centerX - textOffsetX, centerY - textOffsetY);
}

void ResourceSlotUI::Update()
{
}

void ResourceSlotUI::Render(const std::unique_ptr<sf::RenderWindow>& _window) const
{
	_window->draw(boundingBox);
	_window->draw(textBoundingBox);
	_window->draw(iconSprite);
	_window->draw(amountText);
}
