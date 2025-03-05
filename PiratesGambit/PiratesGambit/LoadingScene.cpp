#include "LoadingScene.h"

#include "GamePlayScene.h"
#include "MainMenuScene.h"
#include "SceneManager.h"

LoadingScene::LoadingScene()
{
    generationThread = std::thread([this]() {
        nextScene = generateNextScene();
        sceneReady = true;
        });

    loadingText.setFont(TextureManager::getInstance().getFont());
    loadingText.setString("Loading...");
    loadingText.setCharacterSize(30);
    loadingText.setFillColor(sf::Color::White);
    loadingText.setPosition(350, 250);

    rotatingSquare.setSize(sf::Vector2f(50, 50));
    rotatingSquare.setFillColor(sf::Color(100, 250, 100));
    rotatingSquare.setOrigin(25, 25); // Set origin to center for smooth rotation
    rotatingSquare.setPosition(400, 350); // Center of screen
}

void LoadingScene::handleInput(const std::unique_ptr<sf::RenderWindow>& window, sf::Event newEvent)
{
}

void LoadingScene::update(float dt)
{
    if (sceneReady) {
        SceneManager::getInstance().setScene(nextScene);
        return;
    }

    rotatingSquare.rotate(rotationSpeed * (dt * 0.001f));
}

void LoadingScene::render(const std::unique_ptr<sf::RenderWindow>& window)
{
    window->draw(loadingText);
    window->draw(rotatingSquare);
}

Scene* LoadingScene::generateNextScene()
{
    auto gamePlayScene = new GamePlayScene();
    return gamePlayScene; // Replace with your actual scene
}
