#include "EnemyBoat.h"
#include"Enemy.h"

EnemyBoat::EnemyBoat(const std::shared_ptr<Enemy>& _refEnemy, const UnitAllegiance& _allegiance)
{
	enemyRef = _refEnemy;

	decideSprite();
	boatSprite.setOrigin(56, 33);
	boatSprite.setScale(0.5, 0.5);

	myHitbox = new HitBox(sf::Vector2f(56, 25));
}

void EnemyBoat::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	window->draw(boatSprite);
	for (auto& leaf : smokeParticles)
	{
		leaf.Render(window);
	}
}

void EnemyBoat::update(double dt)
{
	createSmokeParticles(dt);
}

void EnemyBoat::takeDamage()
{
	totalHealth -= 10;
	decideSprite();
}

void EnemyBoat::decideSprite()
{
	if (totalHealth <= 40)
	{
		boatSprite.setTexture(TextureManager::getInstance().getBoatTexture(enemyRef->GetFactionAllegiance(), "BROKEN"));
		emitionRate = 0.1f;
	}
	else if (totalHealth <= 70)
	{
		boatSprite.setTexture(TextureManager::getInstance().getBoatTexture(enemyRef->GetFactionAllegiance(), "DAMAGED"));
		emitionRate = 0.05f;
	}
	else
	{
		boatSprite.setTexture(TextureManager::getInstance().getBoatTexture(enemyRef->GetFactionAllegiance(), "HEALTHY"));
	}
}

void EnemyBoat::RotateTowardsPlayer(sf::Vector2f _pos)
{
    if (_pos.x != 0 || _pos.y != 0)
    {
        float targetAngle = std::atan2(_pos.y, _pos.x) * 180 / Utility::PI;

        float currentAngle = boatSprite.getRotation();

        float angleDiff = targetAngle - currentAngle;
        if (angleDiff > 180) angleDiff -= 360;
        if (angleDiff < -180) angleDiff += 360;

        float rotationSpeed = 0.075f; 
        float newAngle = currentAngle + angleDiff * rotationSpeed;

        boatSprite.setRotation(newAngle);
    }
}

void EnemyBoat::setShipTexture(const UnitAllegiance& _allegiance)
{
	switch (_allegiance)
	{
	case YELLOW_PLAYER:
		boatSprite.setTexture(TextureManager::getInstance().getTexture("YELLOW_SHIP"));
		break;
	case RED_PLAYER:
		boatSprite.setTexture(TextureManager::getInstance().getTexture("RED_SHIP"));
		break;
	case BLUE_PLAYER:
		boatSprite.setTexture(TextureManager::getInstance().getTexture("BLUE_SHIP"));
		break;
	case GREEN_PLAYER:
		boatSprite.setTexture(TextureManager::getInstance().getTexture("GREEN_SHIP"));
		break;
	case BLACK_PLAYER:
		boatSprite.setTexture(TextureManager::getInstance().getTexture("BLACK_SHIP"));
		break;
	default:
		break;
	}

}

void EnemyBoat::createSmokeParticles(double _dt)
{
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> chance(0.f, 1.f);
	std::uniform_real_distribution<double> x(-10,10);

	if (chance(gen) < emitionRate) // 0.15% chance per frame
	{
		sf::Vector2f leafPos = boatSprite.getPosition();
		//leafPos.y -= (rand() % 20) + 30;
		leafPos.x += x(gen);
		smokeParticles.emplace_back(leafPos);
	}

	for (auto& leaf : smokeParticles)
	{
		leaf.Update(_dt);
	}

	std::erase_if(smokeParticles, [](const Particle& particle) {
		return particle.isMarkedForDeletion();
		});
}
