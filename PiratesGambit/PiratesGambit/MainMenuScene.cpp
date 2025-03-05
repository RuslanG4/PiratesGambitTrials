#include "MainMenuScene.h"

#include "LoadingScene.h"
#include "SceneManager.h"

MainMenuScene::MainMenuScene()
{
    background.setTexture(TextureManager::getInstance().getTexture("SEA_BG"));
    background.setScale(SCREEN_WIDTH / TextureManager::getInstance().getTexture("SEA_BG").getSize().x, SCREEN_HEIGHT / TextureManager::getInstance().getTexture("SEA_BG").getSize().y);

    playButton.setFont(TextureManager::getInstance().getFont());
    playButton.setString("Play");
    playButton.setCharacterSize(100);
    playButton.setFillColor(sf::Color::Black);
    centerText(playButton, 350);

    quitButton.setFont(TextureManager::getInstance().getFont());
    quitButton.setString("Quit");
    quitButton.setCharacterSize(100);
    quitButton.setFillColor(sf::Color::Black);
    centerText(quitButton, 550);
}

void MainMenuScene::handleInput(const std::unique_ptr<sf::RenderWindow>& window, sf::Event newEvent)
{
    // Hover effect
    if (isMouseOver(playButton, window)) {
        playButton.setCharacterSize(110);
    }
    else {
        playButton.setCharacterSize(100);
    }
    centerText(playButton, 350);

    if (isMouseOver(quitButton, window)) {
        quitButton.setCharacterSize(110);
    }
    else {
        quitButton.setCharacterSize(100);
    }
    centerText(quitButton, 550);

    // Handle clicks
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (isMouseOver(playButton, window)) {
            SceneManager::getInstance().setScene(new LoadingScene());
        }
        else if (isMouseOver(quitButton, window)) {
            window->close();
        }
    }
}

void MainMenuScene::update(float dt)
{
}

void MainMenuScene::render(const std::unique_ptr<sf::RenderWindow>& window)
{
    window->draw(background);
    window->draw(playButton);
    window->draw(quitButton);
}

void MainMenuScene::centerText(sf::Text& text, float y)
{
    text.setPosition(400 - text.getGlobalBounds().getSize().x / 2, y);
}

bool MainMenuScene::isMouseOver(sf::Text& text, const std::unique_ptr<sf::RenderWindow>& window)
{
    sf::FloatRect bounds = text.getGlobalBounds();
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getInstance().getMousePosition());
    return bounds.contains(mousePos);
}
