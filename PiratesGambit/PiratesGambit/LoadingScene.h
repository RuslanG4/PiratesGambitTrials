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

    std::vector<std::string> loadTooltips(const std::string& filename);

    void centerText(sf::Text& _text, int _y);

	Scene* generateNextScene();
private:
    std::thread generationThread;
    std::atomic<bool> sceneReady{ false };
    Scene* nextScene = nullptr;

    sf::Sprite background;
    sf::Sprite rotatingSquare;
    float rotationSpeed = 100.0f;

    std::vector<std::string> toolTips;

    sf::Clock clock;
    sf::Font font;
    sf::Text loadingText;

    sf::Text toolTipText;
};

