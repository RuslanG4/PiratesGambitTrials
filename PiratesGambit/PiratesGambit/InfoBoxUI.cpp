#include "InfoBoxUI.h"

InfoBoxUI::InfoBoxUI(float _scaleX, float _scaleY)
{
	topText.setFont(TextureManager::getInstance().getFont());
	topText.setCharacterSize(20);

	bottomText.setFont(TextureManager::getInstance().getFont());
	bottomText.setCharacterSize(20);

    backgroundSprite.setTexture(TextureManager::getInstance().getTexture("ARMY_MENU_UI"));
    backgroundSprite.setScale(_scaleX, _scaleY);

}

void InfoBoxUI::Render(const std::unique_ptr<sf::RenderWindow>& _window) const
{
	_window->draw(backgroundSprite);
	_window->draw(topText);
	if (hasIcon && icon.getTexture() != nullptr) {
		_window->draw(icon);
	}
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
    backgroundSprite.setPosition(_pos);
    UpdateLayout();
}

void InfoBoxUI::UpdateText(const std::string& _text)
{
	bottomText.setString(_text);
}

void InfoBoxUI::RemoveIcon()
{
	hasIcon = false;
	UpdateLayout();
}

void InfoBoxUI::UpdateLayout()
{
    // Get the size of the border
    sf::Vector2f borderSize = backgroundSprite.getGlobalBounds().getSize();

    // Scale and position the top text
    float topTextMaxWidth = borderSize.x * 0.9f; // Leave some padding
    float topTextScaleFactor = topTextMaxWidth / topText.getGlobalBounds().width;
    if (topTextScaleFactor < 1.0f) {
        topText.setCharacterSize(static_cast<unsigned int>(topText.getCharacterSize() * topTextScaleFactor));
    }
    topText.setPosition(
        backgroundSprite.getPosition().x + (borderSize.x / 2 - topText.getLocalBounds().width / 2),
        backgroundSprite.getPosition().y + 5
    );

    // Scale and position the bottom text
    float bottomTextMaxWidth = borderSize.x * 0.9f; // Leave some padding
    float bottomTextScaleFactor = bottomTextMaxWidth / bottomText.getGlobalBounds().width;
    if (bottomTextScaleFactor < 1.0f) {
        bottomText.setCharacterSize(static_cast<unsigned int>(bottomText.getCharacterSize() * bottomTextScaleFactor));
    }
    bottomText.setPosition(
        backgroundSprite.getPosition().x + (borderSize.x / 2 - bottomText.getLocalBounds().width / 2),
        backgroundSprite.getPosition().y + borderSize.y - 30
    );

    // If there is an icon, scale and position it
    if (hasIcon) {
        float iconMaxSize = std::min(borderSize.x * 0.8f, borderSize.y * 0.6f); // Limit the icon size
        float iconScaleFactor = iconMaxSize / std::max(icon.getTextureRect().width, icon.getTextureRect().height);
        icon.setScale(iconScaleFactor, iconScaleFactor);

        icon.setPosition(
            backgroundSprite.getPosition().x + (borderSize.x / 2 - icon.getGlobalBounds().width / 2),
            backgroundSprite.getPosition().y + (borderSize.y / 2 - icon.getGlobalBounds().height / 2)
        );
    }
}
