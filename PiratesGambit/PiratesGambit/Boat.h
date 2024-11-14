#pragma once
#include"Includes.h"
#include "TextureManager.h"
#include "PlayerController.h"

class Boat
{
public:
	Boat()
	{
		boatSprite.setTexture(TextureManager::getInstance().getTexture("PLAYER_BOAT"));

		boatSprite.setOrigin(56, 33);
		boatSprite.setScale(0.5, 0.5);

	}

	void render(sf::RenderWindow& window) const { window.draw(boatSprite); }

	void deflect(PlayerController* _controller);

	sf::Vector2f getPosition() const { return position; }
	int getCurrentNodeID() const { return currentNodeID; }
	void setPosition(sf::Vector2f _pos) { position = _pos; boatSprite.setPosition(position); }
	void setRotation(float _rotation){ boatSprite.setRotation(_rotation); }
	void setCurrentNodeID(int _id) { currentNodeID = _id; }
private:
	sf::Vector2f position;
	sf::Sprite boatSprite;

	int currentNodeID;

};

