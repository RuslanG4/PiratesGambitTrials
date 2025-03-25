#include "UnitStatsDisplay.h"

UnitStatsDisplay::UnitStatsDisplay()
{
	isOpen = false;

	background.setTexture(TextureManager::getInstance().getTexture("PLAYER_MENU_UI"));
	background.setScale(3, 4);
	//background.setOrigin(48, 48);

    speedText.setFont(TextureManager::getInstance().getFont("Comic"));
    speedText.setCharacterSize(30U);
    attackText.setFont(TextureManager::getInstance().getFont("Comic"));
    attackText.setCharacterSize(30U);
    defenceText.setFont(TextureManager::getInstance().getFont("Comic"));
    defenceText.setCharacterSize(30U);
    damageRange.setFont(TextureManager::getInstance().getFont("Comic"));
    damageRange.setCharacterSize(30U);
    health.setFont(TextureManager::getInstance().getFont("Comic"));
    health.setCharacterSize(30U);
    initiative.setFont(TextureManager::getInstance().getFont("Comic"));
    initiative.setCharacterSize(30U);

}

void UnitStatsDisplay::Render(const std::unique_ptr<sf::RenderWindow>& _win) const
{
	if(isOpen)
	{
		_win->draw(background);
		_win->draw(speedText);
		_win->draw(attackText);
		_win->draw(defenceText);
		_win->draw(damageRange);
		_win->draw(health);
		_win->draw(initiative);
	}
}

void UnitStatsDisplay::updateDisplay(UnitStats _stats)
{
    speedText.setString("Speed : " + std::to_string(_stats.speed));
    attackText.setString("Attack : " + std::to_string(_stats.attackStat));
    defenceText.setString("Defence : " + std::to_string(_stats.defenceStat));
    damageRange.setString("Damage : " + std::to_string(_stats.minDamage) + "-"+ std::to_string(_stats.maxDamage));
    health.setString("Health : " + std::to_string(_stats.health));
    initiative.setString("Initiative : " + std::to_string(_stats.initiative));
}

void UnitStatsDisplay::setPosition(sf::Vector2f _pos)
{
    sf::Vector2f pos = _pos - sf::Vector2f(0, background.getGlobalBounds().height);
	background.setPosition(pos);
	placeText();
}

void UnitStatsDisplay::placeText()
{
    sf::FloatRect backgroundBounds = background.getGlobalBounds();
    float backgroundWidth = backgroundBounds.width;
    float backgroundHeight = backgroundBounds.height;

    std::vector<sf::Text*> texts = { &speedText, &attackText, &defenceText, &damageRange, &health, &initiative };
    float totalTextHeight = 0;
    float maxWidth = 0;

    for (auto* text : texts) {
        sf::FloatRect textBounds = text->getGlobalBounds();
        totalTextHeight += textBounds.height;
        if (textBounds.width > maxWidth) {
            maxWidth = textBounds.width;
        }
    }

    float spaceBetweenText = 5.0f;  

    float totalHeight = totalTextHeight + (spaceBetweenText * (texts.size() - 1));
    float startY = (backgroundHeight - totalHeight) / 2;

    float currentY = startY;
    for (auto* text : texts) {
        sf::FloatRect textBounds = text->getGlobalBounds();
        float centerX = (backgroundWidth - textBounds.width) / 2;

        text->setPosition(background.getPosition().x + centerX, background.getPosition().y + currentY);

        currentY += textBounds.height + spaceBetweenText;
    }
}

