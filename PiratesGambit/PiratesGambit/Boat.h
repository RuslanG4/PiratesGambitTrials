#ifndef BOAT_H
#define BOAT_H
#include"Includes.h"
#include "TextureManager.h"
#include "BoatController.h"
#include"Node.h"
#include "HitBox.h"

class Player; 

class Boat
{
public:
	Boat(sf::Vector2f _pos, const std::shared_ptr<Player>& _refPlayer)
	{
		currentPlayer = _refPlayer;
		controller = new BoatController(_pos);

		boatSprite.setTexture(TextureManager::getInstance().getTexture("PLAYER_BOAT"));
		boatSprite.setOrigin(56, 33);
		boatSprite.setScale(0.5, 0.5);

		myHitbox = new HitBox(sf::Vector2f(56,33));
	}

	void render(sf::RenderWindow& window) const;

	void update(double dt);

	void deflect(BoatController* _controller);
	bool checkCollision(Node*& _node, sf::Vector2f& _pos);

	sf::Vector2f getPosition() const { return position; }
	int getCurrentNodeID() const { return currentNodeID; }
	BoatController* getController() const { return controller; }
	Node* getDockedNode() const { return dockedNode; }
	void setPosition(sf::Vector2f _pos) { position = _pos; boatSprite.setPosition(position); }
	void setRotation(float _rotation){ boatSprite.setRotation(_rotation); }
	void setCurrentNodeID(int _id) { currentNodeID = _id; }
private:
	sf::Vector2f position;
	sf::Sprite boatSprite;

	HitBox* myHitbox;
	Node* dockedNode;

	BoatController* controller;
	std::shared_ptr<Player> currentPlayer;

	int currentNodeID;

};

#endif // BOAT_H
