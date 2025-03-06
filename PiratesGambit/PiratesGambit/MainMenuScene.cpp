#include "MainMenuScene.h"

#include "LoadingScene.h"
#include "SceneManager.h"

MainMenuScene::MainMenuScene()
{
    background.setTexture(TextureManager::getInstance().getTexture("SEA_BG"));
    background.setScale(10, 9);

    playButton = std::make_unique<Button>(sf::Vector2f(400, 300), "Play");
    ExitButton = std::make_unique<Button>(sf::Vector2f(400, 475), "Quit");
}

void MainMenuScene::handleInput(const std::unique_ptr<sf::RenderWindow>& window, sf::Event newEvent)
{
    playButton->handleEvent(newEvent);
    ExitButton->handleEvent(newEvent);

    if(playButton->isClicked())
    {
        SceneManager::getInstance().setScene(new LoadingScene());
    }else if(ExitButton->isClicked())
    {
        window->close();
    }
}

void MainMenuScene::update(float dt)
{
}

void MainMenuScene::render(const std::unique_ptr<sf::RenderWindow>& window)
{
    window->draw(background);
    playButton->draw(window);
    ExitButton->draw(window);
}

