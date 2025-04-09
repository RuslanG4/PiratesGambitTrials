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
    detectPlayerClock.restart();
	targetNode = playerRef->getCurrentNode();
    FindNewPath(enemy);
}

void FollowPlayerState::Update(Enemy& enemy, float deltaTime)
{
	if (targetNode != playerRef->getCurrentNode()) {
		FindNewPath(enemy);

		// If player has gone out of update radius
		auto playerTooFar = std::find_if(enemy.getUpdateableArea()->getUpdateableNodes().begin(),
			enemy.getUpdateableArea()->getUpdateableNodes().end(),
			[&](const std::shared_ptr<Node>& node) {
				return node->getID() == playerRef->getCurrentNode()->getID();
			});
		// back to wandering, minus player rep
		if (playerTooFar == enemy.getUpdateableArea()->getUpdateableNodes().end()) {
			enemy.updateAllegiance(-10);
			enemy.ChangeState(new EnemyBoatWander(playerRef));
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

    if (!path.empty()) {
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

	path = PathFindingFunctions<Node>::aStarPathFind(enemy.getCurrentNode(), destinationNode, enemy.isOnBoat());
    
}

void FollowPlayerState::FollowLeader(Enemy& enemy)
{
	float speed = 0.8f;
    if (currentNodeInPath >= path.size()) {
        path.clear();
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
            path.clear();
            return;
        }
        distance = path[currentNodeInPath]->getMidPoint() - enemy.GetPosition();
    }

    distance = Utility::unitVector2D(distance);

    enemy.FaceDirection(distance);

    enemy.SetPosition(enemy.GetPosition() + distance * speed);
}
