#include "InfoBoxUI.h"

InfoBoxUI::InfoBoxUI()
{
	topText.setFont(TextureManager::getInstance().getFont());
	topText.setCharacterSize(20);

	bottomText.setFont(TextureManager::getInstance().getFont());
	bottomText.setCharacterSize(20);

	Border.setFillColor(sf::Color::Transparent);
	Border.setOutlineColor(sf::Color::Black);
	Border.setOutlineThickness(3);
}

void InfoBoxUI::Render(const std::unique_ptr<sf::RenderWindow>& _window) const
{
	_window->draw(Border);
	_window->draw(topText);
	if (hasIcon) _window->draw(icon);
	_window->draw(bottomText);
}

void InfoBoxUI::Update()
{
}

void InfoBoxUI::setText(const std::string& top, const std::string& bottom)
{
	topText.setString(top);
	bottomText.setString(bottom);
	UpdateLayout();
}

void InfoBoxUI::SetIcon(const sf::Texture& _texture)
{
	icon.setTexture(_texture);
	hasIcon = true;
	UpdateLayout();
}

void InfoBoxUI::setPosition(sf::Vector2f _pos)
{
	Border.setPosition(_pos);
	topText.setPosition(_pos.x + (Border.getSize().x / 2 - topText.getLocalBounds().width / 2), _pos.y + 5);
	bottomText.setPosition(_pos.x + (Border.getSize().x / 2 - bottomText.getLocalBounds().width / 2), _pos.y + Border.getSize().y - 30);
	if (hasIcon)
		icon.setPosition(_pos.x + (Border.getSize().x / 2 - icon.getGlobalBounds().width / 2), _pos.y + Border.getSize().y / 2 - 20);
}

void InfoBoxUI::RemoveIcon()
{
	hasIcon = false;
	UpdateLayout();
}

void InfoBoxUI::UpdateLayout()
{
	float width = std::max(topText.getLocalBounds().width, bottomText.getLocalBounds().width) + 20;
	float height = 80; // Minimum height

	if (hasIcon) {
		height += 40; // Extra space for icon
		icon.setPosition(width / 2 - icon.getGlobalBounds().width / 2, height / 2 - 20);
	}

	topText.setPosition(width / 2 - topText.getLocalBounds().width / 2, 5);
	bottomText.setPosition(width / 2 - bottomText.getLocalBounds().width / 2, height - 30);

	Border.setSize(sf::Vector2f(width, height));
}
