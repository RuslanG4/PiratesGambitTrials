#pragma once
#include"Includes.h"
#include"HomeScreenButton.h"
#include"SceneManager.h"
#include"MainMenuScene.h"
class PauseScreen
{
public:
    static PauseScreen& getInstance()
    {
        static PauseScreen instance;
        return instance;
    }

    void Render(std::unique_ptr<sf::RenderWindow>& _window) const {
		if (isOpen) {
            _window->setView(_window->getDefaultView());
			_window->draw(background);
			homeButton->draw(_window);
			returnButton->draw(_window);
		}
    };

    void Update(sf::Event newEvent) {
		homeButton->handleEvent(newEvent);
		returnButton->handleEvent(newEvent);

		if (returnButton->isClicked())
		{
            CloseMenu();
			returnButton->resetButton();
		}
		else
		if (homeButton->isClicked())
		{
			SceneManager::getInstance().setScene(new MainMenuScene());
            CloseMenu();
			homeButton->resetButton();
		}

		bool currentEscapePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

		if (currentEscapePressed && !previousEscapePressed)
		{
			CloseMenu();
		}

		previousEscapePressed = currentEscapePressed;

    };

    void OpenMenu() { isOpen = true; }

    void CloseMenu() { isOpen = false; }

    bool isOpened() const { return isOpen; }

private:
    PauseScreen()
    {
        background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        background.setFillColor(sf::Color(0, 0, 0, 150));

		homeButton = std::make_unique<HomeScreenButton>(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100), "Home");
		returnButton = std::make_unique<HomeScreenButton>(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100), "Return");
   
    }

    PauseScreen(const PauseScreen&) = delete;
    PauseScreen& operator=(const PauseScreen&) = delete;

	bool previousEscapePressed=true;
    bool isOpen = false;
    sf::RectangleShape background;
	std::unique_ptr<HomeScreenButton> homeButton;
    std::unique_ptr<HomeScreenButton> returnButton;
   
};

