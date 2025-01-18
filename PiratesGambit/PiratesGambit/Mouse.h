#pragma once
#include"Includes.h"
#include "TextureManager.h"

class Mouse
{
public:
	static Mouse& getInstance() {
		static Mouse instance;
		return instance;
	}

	void update(const std::unique_ptr<sf::RenderWindow>& window);

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

	void SetToRanged()
	{
		if (!customCursor.loadFromPixels(rangedCursor.getPixelsPtr(), rangedCursor.getSize(), sf::Vector2u(2, 2))) {
			std::cerr << "Failed to create custom cursor!";
		}
		windowRef->setMouseCursor(customCursor);
	}

	void SetToDefault()
	{
		if (!customCursor.loadFromSystem(sf::Cursor::Arrow)) {
			std::cerr << "Failed to load default cursor!";
		}
		windowRef->setMouseCursor(customCursor);
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
		renderTexture.create(48, 48); // Double the size (example)
		sf::Sprite sprite;
		sprite.setTexture(TextureManager::getInstance().getTexture("SHOOT_ICON"));
		sprite.setScale(1.5f, 1.5f); // Scale factor

		renderTexture.draw(sprite);

		rangedCursor = renderTexture.getTexture().copyToImage();
		rangedCursor.flipHorizontally();
		rangedCursor.flipVertically();
	}
	sf::Vector2i mousePosition;

	sf::RenderWindow* windowRef;

	sf::RenderTexture renderTexture;
	sf::Image rangedCursor;
	sf::Cursor customCursor;

	bool canClick{ true };
	bool hasClickedRight{ false };
	bool hasClickedLeft{ false };
};

