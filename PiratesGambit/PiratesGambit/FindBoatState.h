#pragma once
#include "EnemyState.h"
#include "Node.h"
#include "Player.h"

class FindBoatState :
    public EnemyState
{
public:
	FindBoatState(const std::shared_ptr<Player>& _playerRef) : playerRef(_playerRef)
	{
		currentNodeInPath = 0;
	}

	void Enter(Enemy& enemy) override;
	void Update(Enemy& enemy, float deltaTime) override;
	void Exit(Enemy& enemy) override;

	void ChasePlayer(Enemy& enemy);
private:
	std::shared_ptr<Player> playerRef;
	std::vector<std::shared_ptr<Node>> path;
	int currentNodeInPath = 0;
};

