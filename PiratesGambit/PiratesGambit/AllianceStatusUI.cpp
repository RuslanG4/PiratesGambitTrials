#include "AllianceStatusUI.h"

#include "TextureManager.h"

AllianceStatusUI::AllianceStatusUI(sf::Vector2f _pos)
{
    background.setSize(sf::Vector2f(250, 250));
    background.setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent gray

    costText.setFont(TextureManager::getInstance().getFont("Varsity"));
    costText.setCharacterSize(36U);
    costText.setFillColor(sf::Color::White);
    costText.setString("1000");

    alligianceText.setFont(TextureManager::getInstance().getFont("Varsity"));
    alligianceText.setCharacterSize(36U);
    alligianceText.setFillColor(sf::Color::White);
    alligianceText.setString(("Allegiance"));

    allegianceBar.setFillColor(sf::Color::Black);

    allegianceBarSlider.setSize(sf::Vector2f(10, 20));
    allegianceBarSlider.setOrigin(5, 10);
    allegianceBarSlider.setFillColor(sf::Color::Cyan);

    for(int i =0; i< 3; i++)
    {
        allegianceCircles.push_back(sf::CircleShape());
        allegianceCircles[i].setRadius(8.f);
        allegianceCircles[i].setOrigin(8, 8);
    }
    allegianceCircles[0].setFillColor(sf::Color::Red);
    allegianceCircles[1].setFillColor(sf::Color::Yellow);
    allegianceCircles[2].setFillColor(sf::Color::Green);

    background.setPosition(_pos);
    allegianceBar.setPosition(background.getPosition().x + 40, background.getPosition().y + 100);
    ScaleAllegianceBar();
    CenterTexts();
}

void AllianceStatusUI::Render(const std::unique_ptr<sf::RenderWindow>& _window) const
{
    //_window->draw(background);
    _window->draw(costText);
    _window->draw(alligianceText);
    _window->draw(allegianceBar);
    _window->draw(allegianceBarSlider);
    for(auto& circle : allegianceCircles)
    {
        _window->draw(circle);
    }
}

void AllianceStatusUI::updateAllegianceLevel(const AllegianceLevel& _level)
{
    switch (_level) {
    case AllegianceLevel::Hostile:
        allegianceBarSlider.setFillColor(sf::Color::Red);
        break;
    case AllegianceLevel::Neutral:
        allegianceBarSlider.setFillColor(sf::Color::Yellow);
        break;
    case AllegianceLevel::Friendly:
        allegianceBarSlider.setFillColor(sf::Color::Green);
        break;
    }
}

void AllianceStatusUI::ScaleAllegianceBar()
{
    float barWidth = background.getSize().x - 80;
    allegianceBar.setSize(sf::Vector2f(barWidth, 15));

    allegianceCircles[0].setPosition(allegianceBar.getPosition() + sf::Vector2f(0, -25));
    allegianceCircles[1].setPosition(allegianceBar.getPosition() + sf::Vector2f(allegianceBar.getSize().x / 2, -25));
    allegianceCircles[2].setPosition(allegianceBar.getPosition() + sf::Vector2f(allegianceBar.getSize().x, -25));
    allegianceBarSlider.setPosition(allegianceBar.getPosition().x, allegianceBar.getPosition().y + allegianceBar.getSize().y / 2);
}

void AllianceStatusUI::PlaceIndicatorOnAllegianceBar(int _value)
{
	float barWidth = allegianceBar.getSize().x;
    _value = std::clamp(_value, 0, 100);
    float sliderPosX = allegianceBar.getPosition().x + (barWidth * (_value / 100.f));
	allegianceBarSlider.setPosition(sliderPosX, allegianceBar.getPosition().y + allegianceBar.getSize().y / 2);

    int baseCost = 2000; 

    float multiplier = 1.0f + (1.0f - (_value / 100.0f));
    int cost = static_cast<int>(baseCost * multiplier);

	costText.setString(std::to_string(cost));
    costAmount = cost;
}

void AllianceStatusUI::CenterTexts()
{
    sf::Vector2f bgPos = background.getPosition();
    sf::Vector2f bgSize = background.getSize();

    sf::FloatRect allegianceBounds = alligianceText.getLocalBounds();
    alligianceText.setOrigin(allegianceBounds.width / 2, allegianceBounds.height / 2);
    alligianceText.setPosition(bgPos.x + bgSize.x / 2, bgPos.y + 20);

    sf::FloatRect costBounds = costText.getLocalBounds();
    costText.setOrigin(costBounds.width / 2, costBounds.height / 2);
    costText.setPosition(bgPos.x + bgSize.x / 2, bgPos.y + bgSize.y * 0.75f);
}
