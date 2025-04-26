#include "FollowPlayerState.h"

#include "Enemy.h"
#include "FindBoatState.h"
#include "IdleState.h"
#include"EnemyBoatWander.h"
#include "PathFindingFunctions.h"
#include"ChaseState.h"

void FollowPlayerState::Enter(Enemy& enemy)
{
	std::cout << "Enemy is entering Fleet state." << std::endl;
	enemy.SetAnimationState(UnitState::WALK);
	detectPlayerClock.restart();
	targetNode = playerRef->getCurrentNode();
	FindNewPath(enemy);
}

void FollowPlayerState::Update(Enemy& enemy, float deltaTime)
{
	if (targetNode != playerRef->getCurrentNode()) {
		FindNewPath(enemy);
		if (playerRef->isOnBoat() && !enemy.isOnBoat())
		{
			path.clear();
		}
		else {

			// If player has gone out of update radius
			auto playerTooFar = std::find_if(enemy.getUpdateableArea()->getUpdateableNodes().begin(),
				enemy.getUpdateableArea()->getUpdateableNodes().end(),
				[&](const std::shared_ptr<Node>& node) {
					return node->getID() == playerRef->getCurrentNode()->getID();
				});
			// back to wandering, minus player rep
			if (playerTooFar == enemy.getUpdateableArea()->getUpdateableNodes().end()) {
				enemy.updateAllegiance(-10);
				enemy.updateHiredStatus(false);
				if (enemy.isOnBoat()) {
					enemy.ChangeState(new IdleState(playerRef));
				}
				else {
					enemy.ChangeState(new EnemyBoatWander(playerRef));
				}
				return;
			}

			if (enemy.GetPlayerAllegiance().isHostile()) {
				for (auto& node : enemy.getUpdateableArea()->getUpdateableNodes())
				{
					if (node == playerRef->getCurrentNode())
					{
						enemy.ChangeState(new ChaseState(playerRef));
						break;
					}
				}
			}
		}

	}
	if (playerRef->isOnBoat() && !enemy.isOnBoat())
	{
		enemy.ChangeState(new FindBoatState(playerRef));
	}

	else if (!path.empty()) {
		FollowLeader(enemy);
	}
}

void FollowPlayerState::Exit(Enemy& enemy)
{
	std::cout << "Enemy is leaving chase state.";
}

void FollowPlayerState::FindNewPath(Enemy& enemy)
{
	switch (playerRef->GetDirection())
	{
	case NORTH:
		for (auto& node : playerRef->getCurrentNode()->getNeighbours()) {
			if (node.second == 2 || node.second == 5 || node.second == 8)
			{
				if (!node.first->getIsLand() && !node.first->isOccupied()) {
					destinationNode = (node.first);
					break;
				}
			}
		}

		break;
	case SOUTH:
		for (auto& node : playerRef->getCurrentNode()->getNeighbours()) {
			if (node.second == 0 || node.second == 3 || node.second == 6)
			{
				if (!node.first->getIsLand() && !node.first->isOccupied()) {
					destinationNode = (node.first);
					break;
				}
			}
		}
		break;
	case EAST:
		for (auto& node : playerRef->getCurrentNode()->getNeighbours()) {
			if (node.second == 0 || node.second == 1 || node.second == 2)
			{
				if (!node.first->getIsLand() && !node.first->isOccupied()) {
					destinationNode = (node.first);
					break;
				}
			}
		}
		break;
	case WEST:
		for (auto& node : playerRef->getCurrentNode()->getNeighbours()) {
			if (node.second == 6 || node.second == 7 || node.second == 8)
			{
				if (!node.first->getIsLand() && !node.first->isOccupied()) {
					destinationNode = (node.first);
					break;
				}
			}
		}
		break;
	}

	targetNode = playerRef->getCurrentNode();
	currentNodeInPath = 0;

	path.clear();

	if (!playerRef->isOnBoat())
	{
		if (enemy.isOnBoat()) {
			path = PathFindingFunctions<Node>::generalAStarPathFind(enemy.getCurrentNode(), playerRef->getCurrentNode());
		}
		else {
			path = PathFindingFunctions<Node>::aStarPathFind(enemy.getCurrentNode(), playerRef->getCurrentNode(), enemy.isOnBoat());
		}
		currentNodeInPath = 0;

	}
	else if (playerRef->isOnBoat() && enemy.isOnBoat())
	{
		path = PathFindingFunctions<Node>::aStarPathFind(enemy.getCurrentNode(), destinationNode, enemy.isOnBoat());
	}


	//path = PathFindingFunctions<Node>::aStarPathFind(enemy.getCurrentNode(), destinationNode, enemy.isOnBoat());

}

void FollowPlayerState::FollowLeader(Enemy& enemy)
{
	float speed = 0.8f;
	enemy.SetAnimationState(UnitState::WALK);
	if (currentNodeInPath >= path.size()) {
		path.clear();
		return;
	}
	// Handle disembarking if the next node is land
	if (path[currentNodeInPath]->getIsLand() && enemy.isOnBoat())
	{
		enemy.disembarkBoat(path[currentNodeInPath]);
		path.clear();
		detectPlayerClock.restart();
		return;
	}

	sf::Vector2f distance = path[currentNodeInPath]->getMidPoint() - enemy.GetPosition();
	float magnitude = Utility::magnitude(distance.x, distance.y);

	sf::Vector2f distanceToPlayer = enemy.GetPosition() - playerRef->getPlayerController()->getPosition();
	float magnitudeToPlayer = Utility::magnitude(distanceToPlayer.x, distanceToPlayer.y);

	if (magnitudeToPlayer < 60.0f) {
		speed = 0.3f;
	}


	if (magnitude < 1.0f) {
		currentNodeInPath++;

		// Ensure we don't go out of bounds
		if (currentNodeInPath >= path.size()) {
			enemy.SetAnimationState(UnitState::IDLE);
			path.clear();
			return;
		}
		distance = path[currentNodeInPath]->getMidPoint() - enemy.GetPosition();
	}

	distance = Utility::unitVector2D(distance);

	enemy.FaceDirection(distance);

	enemy.SetPosition(enemy.GetPosition() + distance * speed);
}
