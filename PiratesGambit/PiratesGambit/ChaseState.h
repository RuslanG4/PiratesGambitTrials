#pragma once
#include "EnemyState.h"
#include "Player.h"

class ChaseState :
    public EnemyState
{
public:
	ChaseState(const std::shared_ptr<Player>& _playerRef) : playerRef(_playerRef)
	{
		currentNodeInPath = 0;
	}
	void Enter(Enemy& enemy) override;
	void Update(Enemy& enemy, float deltaTime) override;
	void Exit(Enemy& enemy) override;

	void FindNewPath(const Enemy& enemy);
	void ChasePlayer(Enemy& enemy);

	void FacePlayer(Enemy& enemy, sf::Vector2f distance);
private:
	std::shared_ptr<Player> playerRef;
	std::vector<std::shared_ptr<Node>> path;
	int currentNodeInPath = 0;
	sf::Clock detectPlayerClock;
};

