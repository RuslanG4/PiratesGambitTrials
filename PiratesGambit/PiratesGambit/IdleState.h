#pragma once
#include "EnemyState.h"
#include "Player.h"

class IdleState :
    public EnemyState
{
public:
	IdleState(const std::shared_ptr<Player>& _playerRef) : playerRef(_playerRef)
	{
	}
	void Enter(Enemy& enemy) override;
	void Update(Enemy& enemy, float deltaTime) override;
	void Exit(Enemy& enemy) override;
private:
	std::shared_ptr<Player> playerRef;

};

