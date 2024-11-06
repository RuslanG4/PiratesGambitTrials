#pragma once
#include<SFML/Graphics.hpp>

#include"Utility.h"
#include "Constants.h"

class Player
{
public:
	Player();
	~Player() {};

	void initCamera();

	void update(double dt);
	void render(sf::RenderWindow& window) const;

	void handleKeyInput();
	void move(double dt);

	void increaseSpeed();
	void decreaseSpeed();
	void increaseRotation();
	void decreaseRotation();

	void setSprite(const sf::Texture& texture) { body.setTexture(texture); };
	void setCurrentChunkID(int id_) { currentChunkId = id_; };

	sf::Vector2f getVelocity() const { return vel; };
	sf::View getPlayerCamera() const { return playerCamera; };
	sf::Vector2f getPosition() const { return body.getPosition(); };
	int getCurrentChunkID() const { return currentChunkId; };
private:
	sf::Sprite body;

	sf::View playerCamera;

	double m_speed{ 0.0 };
	double m_rotation{ 0.0 };

	sf::Vector2f vel;
	sf::Vector2f newpos;
	sf::Vector2f m_previousPosition;

	const double MAX_REVERSE_SPEED = -300; //for movement
	const double MAX_FORWARD_SPEED = 300;

	int currentChunkId;

};