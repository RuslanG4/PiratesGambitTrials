#include "IdleState.h"

#include "ChaseState.h"
#include "Enemy.h"

void IdleState::Enter(Enemy& enemy)
{
	std::cout << "Enemy is entering Idle state." << std::endl;
	enemy.SetAnimationState(UnitState::IDLE);
}

void IdleState::Update(Enemy& enemy, float deltaTime)
{
	for (auto& node : enemy.getUpdateableArea()->getUpdateableNodes())
	{
		if (node == playerRef->getCurrentNode() && !playerRef->isOnBoat())
		{
			enemy.ChangeState(new ChaseState(playerRef));
		}
	}
}

void IdleState::Exit(Enemy& enemy)
{
	std::cout << "Enemy is leaving Idle state." << std::endl;
}
