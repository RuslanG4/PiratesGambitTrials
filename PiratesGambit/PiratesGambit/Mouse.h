#pragma once
#include"Includes.h"

class Mouse
{
public:
	static Mouse& getInstance() {
		static Mouse instance;
		return instance;
	}

	void update(sf::RenderWindow& _win);

	void processMouse(sf::Event t_event)
	{
		if (canClick) {
			hasClicked = true;
			canClick = false;
		}
	}
	void processMouseUp(sf::Event t_event)
	{
		hasClicked = false;
		canClick = true;
	}

	sf::Vector2i& getMousePosition() {
		return mousePosition;
	}

	bool& getHasClicked(){
		return hasClicked;
	}

	Mouse(Mouse const&) = delete;
    void operator=(Mouse const&) = delete;
private:
	Mouse()
	{
		
	};
	sf::Vector2i mousePosition;

	bool canClick{ true };
	bool hasClicked{ false };
};

