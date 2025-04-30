#ifndef ENEMYBOAT_H
#define ENEMYBOAT_H
#include"Includes.h"
#include"Node.h"
#include"HitBox.h"
#include"CannonBall.h"
#include"SmokeParticle.h"
#include"BoatTrailParticle.h"

class Enemy;

class EnemyBoat
{
public:
	EnemyBoat(const std::shared_ptr<Enemy>& _refEnemy, const UnitAllegiance& _allegiance);

	void render(const std::unique_ptr<sf::RenderWindow>& window) const;
	void update(double dt);

	void takeDamage();
	void decideSprite();

	void RotateTowardsPlayer(sf::Vector2f _pos);

	sf::Vector2f getPosition() const { return position; }
	const std::shared_ptr<Node>& getDockedNode() const { return dockedNode; }
	bool isAlive() const { return totalHealth > 0; }

	void setPosition(sf::Vector2f _pos);
	void setRotation(float _rotation) { boatSprite.setRotation(_rotation); }
	void setDockedNode(const std::shared_ptr<Node>& _node) { dockedNode = _node; }
	std::shared_ptr<Node> GetDockedNode() const { return dockedNode; }

	sf::FloatRect GetGlobalBounds() const { return boatSprite.getGlobalBounds(); }
	sf::Vector2f getPosition() { return boatSprite.getPosition(); }
	const std::shared_ptr<Enemy>& getEnemyRef() const { return enemyRef; }


private:
	void setShipTexture(const UnitAllegiance& _allegiance);
	void createSmokeParticles(double dt);

	sf::Vector2f position;
	sf::Sprite boatSprite;

	HitBox* myHitbox;
	std::shared_ptr<Node> dockedNode;

	std::vector<std::shared_ptr<CannonBall>> cannonBalls;
	int nextAvailableCannonBall{ 0 };
	bool canShoot{ true };

	std::shared_ptr<Enemy> enemyRef;

	std::random_device rd;
	std::vector<SmokeParticle> smokeParticles;
	float smokeScale;
	float emitionRate;

	int totalHealth = 100;

	std::vector<BoatTrailParticle> waterTrails;
};
#endif // ENEMYBOAT_H