#pragma once
#include"MiniMap.h"

class MiniMapMenu
{
public:
    static MiniMapMenu& getInstance()
    {
        static MiniMapMenu instance;
        return instance;
    }
    void createMiniMap(int _mapSize, int _minimapNodeSize) {
		
        sf::Vector2f miniMapPos = sf::Vector2f(SCREEN_WIDTH / 2 - ((_mapSize * CHUNK_NODE_ROWS * _minimapNodeSize) / 2), SCREEN_HEIGHT / 2 - ((_mapSize * CHUNK_NODE_COLS * _minimapNodeSize) / 2));
        miniMap = std::make_unique<MiniMap>(miniMapPos, _mapSize, _minimapNodeSize);
    }

	std::unique_ptr<MiniMap>& GetMiniMap() {
		return miniMap;
	}

    void Render(const std::unique_ptr<sf::RenderWindow>& _window) const {
        if (isOpen) {
            _window->setView(_window->getDefaultView());
			_window->draw(background);
            miniMap->render(_window);
        }
    };

    void Update() {

    };

    void OpenMenu() { isOpen = true; }

    void CloseMenu() { isOpen = false; }

    bool isOpened() const { return isOpen; }


    MiniMapMenu(const MiniMapMenu&) = delete;
    MiniMapMenu& operator=(const MiniMapMenu&) = delete;

private:
    MiniMapMenu() {
        background.setTexture(TextureManager::getInstance().getTexture("PLAYER_MENU_UI"));
        background.setScale(14, 10);
        background.setOrigin(48, 48);
        background.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
    } 

    bool previousEscapePressed = true;
    bool isOpen = false;
    sf::Sprite background;
    std::unique_ptr<MiniMap> miniMap;

};
