#include "ResourceSlotUI.h"

#include "TextureManager.h"

ResourceSlotUI::ResourceSlotUI(const sf::Texture& _icon, int _amount)
{
	amountText.setFont(TextureManager::getInstance().getFont("Comic"));
	amountText.setCharacterSize(30U);
	amountText.setString(std::to_string(_amount));

	iconSprite.setTexture(_icon);
	iconSprite.setScale(2, 2);
}

void ResourceSlotUI::SetPosition(sf::Vector2f _pos)
{
	boundingBox.setPosition(_pos);
	iconSprite.setPosition(boundingBox.getPosition());
	textBoundingBox.setPosition(sf::Vector2f(iconSprite.getGlobalBounds().left + iconSprite.getGlobalBounds().width + 50,
		iconSprite.getPosition().y+ iconSprite.getGlobalBounds().height / 2));
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
