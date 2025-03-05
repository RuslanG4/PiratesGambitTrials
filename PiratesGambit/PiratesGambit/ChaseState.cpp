#include "ChaseState.h"

#include "Enemy.h"
#include "IdleState.h"
#include "PathFindingFunctions.h"

void ChaseState::Enter(Enemy& enemy)
{
	std::cout << "Enemy is entering chase state." << std::endl;
	enemy.SetAnimationState(UnitState::WALK);
	path = PathFindingFunctions<Node>::aStarPathFind(enemy.getCurrentNode(), playerRef->getCurrentNode()); 
}

void ChaseState::Update(Enemy& enemy, float deltaTime)
{
	FindNewPath(enemy);

	if (!path.empty()) {
		ChasePlayer(enemy);
	} else
	{
		enemy.ChangeState(new IdleState(playerRef));
	}
}

void ChaseState::Exit(Enemy& enemy)
{
	std::cout << "Enemy is leaving chase state." << std::endl;
}

void ChaseState::FindNewPath(const Enemy& enemy)
{
	if (detectPlayerClock.getElapsedTime().asSeconds() >= 1.0f)
	{
		path.clear();
		for (auto& node : enemy.getUpdateableArea()->getUpdateableNodes())
		{
			if (node == playerRef->getCurrentNode() && !playerRef->isOnBoat())
			{
				path = PathFindingFunctions<Node>::aStarPathFind(enemy.getCurrentNode(), playerRef->getCurrentNode());
				currentNodeInPath = 0;
			}
		}
		detectPlayerClock.restart();
	}
}

void ChaseState::ChasePlayer(Enemy& enemy)
{
	sf::Vector2f distance = path[currentNodeInPath]->getMidPoint() - enemy.GetPosition();
	float magnitude = Utility::magnitude(distance.x, distance.y);

	if (magnitude < 2.0f) {
		currentNodeInPath++;

		if (currentNodeInPath >= path.size())
		{
			path.clear();
			return;
		}

		distance = path[currentNodeInPath]->getMidPoint() - enemy.GetPosition();
	}

	distance = Utility::unitVector2D(distance);

	FacePlayer(enemy, distance);
	enemy.SetPosition(enemy.GetPosition() + distance * 1.f); //2.f is speed
}

void ChaseState::FacePlayer(Enemy& enemy, sf::Vector2f distance)
{
	if(distance.x < 0)
	{
		enemy.FacePlayer(-2);
	}else
	{
		enemy.FacePlayer(2);
	}
}

