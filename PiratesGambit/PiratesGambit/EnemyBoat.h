#ifndef ENEMYBOAT_H
#define ENEMYBOAT_H
#include"Includes.h"
#include"Node.h"
#include"HitBox.h"
#include"CannonBall.h"

class Enemy;

class EnemyBoat
{
public:
	EnemyBoat(sf::Vector2f _pos, const std::shared_ptr<Enemy>& _refEnemy, const sf::Texture& _shipTexture)
	{
		enemyRef = _refEnemy;

		position = _pos;
		boatSprite.setTexture(_shipTexture);
		boatSprite.setOrigin(56, 33);
		boatSprite.setPosition(_pos);
		boatSprite.setScale(0.5, 0.5);

		myHitbox = new HitBox(sf::Vector2f(56, 25));
	}

	void render(const std::unique_ptr<sf::RenderWindow>& window) const;
	void update(double dt);

	void RotateTowardsPlayer(sf::Vector2f _pos);

	sf::Vector2f getPosition() const { return position; }
	const std::shared_ptr<Node>& getDockedNode() const { return dockedNode; }

	/*void addCannonBall();
	void fireCannonBall(int _direction);*/

	void setPosition(sf::Vector2f _pos) { position = _pos; boatSprite.setPosition(position); }
	void setRotation(float _rotation) { boatSprite.setRotation(_rotation); }
	void setDockedNode(const std::shared_ptr<Node>& _node) { dockedNode = _node; }
	std::shared_ptr<Node> GetDockedNode() const { return dockedNode; }

private:
	sf::Vector2f position;
	sf::Sprite boatSprite;

	HitBox* myHitbox;
	std::shared_ptr<Node> dockedNode;

	std::vector<std::shared_ptr<CannonBall>> cannonBalls;
	int nextAvailableCannonBall{ 0 };
	bool canShoot{ true };

	std::shared_ptr<Enemy> enemyRef;
};

#endif // ENEMYBOAT_H
