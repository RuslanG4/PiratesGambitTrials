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
			if(t_event.mouseButton.button == sf::Mouse::Left)
			{
				hasClickedLeft = true;
			}
			if (t_event.mouseButton.button == sf::Mouse::Right)
			{
				hasClickedRight = true;
			}
			canClick = false;
		}
	}
	void processMouseUp(sf::Event t_event)
	{
		hasClickedLeft = false;
		hasClickedRight = false;
		canClick = true;
	}

	sf::Vector2i& getMousePosition() {
		return mousePosition;
	}

	bool& LeftClicked(){
		return hasClickedLeft;
	}

	bool& RightClicked() {
		return hasClickedRight;
	}

	Mouse(Mouse const&) = delete;
    void operator=(Mouse const&) = delete;
private:
	Mouse()
	{
		
	};
	sf::Vector2i mousePosition;

	bool canClick{ true };
	bool hasClickedRight{ false };
	bool hasClickedLeft{ false };
};

