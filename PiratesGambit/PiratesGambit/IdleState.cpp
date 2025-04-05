#include "IdleState.h"

#include "AllianceDialogueUI.h"
#include "ChaseState.h"
#include "Enemy.h"
#include "EnemyLandWander.h"
#include "FindBoatState.h"

void IdleState::Enter(Enemy& enemy)
{
	std::cout << "Enemy is entering Idle state." << std::endl;
	enemy.SetAnimationState(UnitState::IDLE);
	waitTimer.restart();
}

void IdleState::Update(Enemy& enemy, float deltaTime)
{
	if (enemy.GetPlayerAllegiance().isHostile()) {
		for (auto& node : enemy.getUpdateableArea()->getUpdateableNodes())
		{
			if (node == playerRef->getCurrentNode())
			{
				enemy.ChangeState(new ChaseState(playerRef));
				break;
			}
		}
	} if(!AllianceDialogueUI::getInstance().isMenuOpen() && waitTimer.getElapsedTime().asSeconds() > 1.5f) //1.5 seconds of idle
	{
		if (enemy.isOnBoat()) {
			enemy.ChangeState(new EnemyBoatWander(playerRef));
		}else
		{
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> disFindShip(1, 10); //10% to go back to boat
			if(disFindShip(gen) == 1)
			{
				enemy.ChangeState(new FindBoatState(playerRef));
			}
			else {
				enemy.ChangeState(new EnemyLandWander(playerRef));
			}
		}
	}
}

void IdleState::Exit(Enemy& enemy)
{
	std::cout << "Enemy is leaving Idle state." << std::endl;
}
