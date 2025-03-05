#pragma once
#include <thread>
#include "Scene.h"
class LoadingScene :
    public Scene
{
public:
	LoadingScene();
    ~LoadingScene() override
    {
        if (generationThread.joinable()) {
            generationThread.join(); // Ensure the thread is joined before destruction
        }
    };

	void handleInput(const std::unique_ptr<sf::RenderWindow>& window, sf::Event newEvent) override;
	void update(float dt) override;
	void render(const std::unique_ptr<sf::RenderWindow>& window) override;

	Scene* generateNextScene();
private:
    std::thread generationThread;
    std::atomic<bool> sceneReady{ false };
    Scene* nextScene = nullptr;

    sf::RectangleShape rotatingSquare;
    float rotationSpeed = 100.0f;

    sf::Font font;
    sf::Text loadingText;
};

