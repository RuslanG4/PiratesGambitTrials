#ifndef BOAT_H
#define BOAT_H
#include"Includes.h"
#include"TextureManager.h"
#include"BoatController.h"
#include"Node.h"
#include"HitBox.h"
#include"CannonBall.h"

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

		fireIndicator.setTexture(TextureManager::getInstance().getTexture("INDICATOR_ICON"));
		fireIndicator.setOrigin(16, 16);
		fireIndicator.setScale(0.5, 0.5);

		myHitbox = new HitBox(sf::Vector2f(56,25));
	}

	void processKeys(sf::Event t_event);
	void processKeyUp(sf::Event t_event);

	void render(const std::unique_ptr<sf::RenderWindow>& window) const;
	void update(double dt);

	bool checkCollision(const std::shared_ptr<Node>& _node, sf::Vector2f& _pos);

	sf::Vector2f getPosition() const { return position; }
	BoatController* getController() const { return controller; }
	const std::shared_ptr<Node>& getDockedNode() const { return dockedNode; }

	void addCannonBall();
	void fireCannonBall(int _direction);

	void setPosition(sf::Vector2f _pos)
	{
		position = _pos;
		boatSprite.setPosition(position);
		controller->setCurrentPosition(position);

	}

	void TakeDamage(int _damage)
	{
		health -= _damage;
		if (health <= 0)
		{
			//handle death
		}
	}

	void updateIndicator();

	void setRotation(float _rotation){ boatSprite.setRotation(_rotation); }
	void setDockedNode(const std::shared_ptr<Node>& _node)
	{
		dockedNode = _node;
		controller->resetVelocity();
	}
private:
	sf::Vector2f position;
	sf::Sprite boatSprite;
	sf::Sprite fireIndicator;

	int fireDirection = 0;

	HitBox* myHitbox;
	std::shared_ptr<Node> dockedNode;

	std::vector<std::shared_ptr<CannonBall>> cannonBalls;
	int nextAvailableCannonBall{ 0 };
	bool canShoot{ true };

	BoatController* controller;
	std::shared_ptr<Player> currentPlayer;

	int health = 100;

};

#endif // BOAT_H
