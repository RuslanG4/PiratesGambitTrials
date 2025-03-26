#pragma once
#include "EnemyState.h"
#include "Player.h"

class EnemyLandWander :
    public EnemyState
{
public:
	EnemyLandWander(const std::shared_ptr<Player>& _player) : playerRef(_player) {}
	void Enter(Enemy& enemy) override;
	void Update(Enemy& enemy, float deltaTime) override;
	void Exit(Enemy& enemy) override;

	void MoveTowardsTarget(Enemy& enemy);
	std::shared_ptr<Node> SelectNextTarget(Enemy& enemy);
	std::vector<std::shared_ptr<Node>> GetValidWaterNodes(Enemy& enemy);
private:
	std::shared_ptr<Player> playerRef;
	std::shared_ptr<Node> targetNode;
	std::vector<std::shared_ptr<Node>> path;
	int currentNodeInPath = 0;
};

