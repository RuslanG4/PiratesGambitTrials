#include "EnemyBoatWander.h"
#include"FollowPlayerState.h"
#include "ChaseState.h"
#include "Enemy.h"
#include "PathFindingFunctions.h"

void EnemyBoatWander::Enter(Enemy& enemy)
{
    std::cout << "Enemy is entering boat wander state." << "\n";
}

void EnemyBoatWander::Update(Enemy& enemy, float deltaTime)
{
    if (path.empty()) {
        targetNode = SelectNextTarget(enemy);
        if (targetNode->getIsLand())
            path = PathFindingFunctions<Node>::generalAStarPathFind(enemy.getCurrentNode(), targetNode);
        else
            path = PathFindingFunctions<Node>::aStarPathFind(enemy.getCurrentNode(), targetNode, enemy.isOnBoat());
    }

    MoveTowardsTarget(enemy);

    if (startTimer) {
		if (boatStuckTimer.getElapsedTime().asSeconds() > 3.0f)
		{
			path.clear();
			currentNodeInPath = 0;
			startTimer = false;
		}
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

void EnemyBoatWander::Exit(Enemy& enemy)
{
    std::cout << "Enemy is leaving boat wander state." << "\n";
}

void EnemyBoatWander::MoveTowardsTarget(Enemy& enemy)
{
    if (currentNodeInPath >= path.size()) {
        path.clear();
        return;
    }

    if (path[currentNodeInPath]->getIsLand() && enemy.isOnBoat())
    {
        enemy.disembarkBoat(path[currentNodeInPath]);
        path.clear();
        enemy.ChangeState(new IdleState(playerRef));
        return;
    }

    sf::Vector2f distance = path[currentNodeInPath]->getMidPoint() - enemy.GetPosition();
    float magnitude = Utility::magnitude(distance.x, distance.y);

    if (magnitude < 2.0f) {
        currentNodeInPath++;

        // Ensure we don't go out of bounds
        if (currentNodeInPath >= path.size()) {
            path.clear();
            currentNodeInPath = 0;
            return;
        }
        distance = path[currentNodeInPath]->getMidPoint() - enemy.GetPosition();
    }

    distance = Utility::unitVector2D(distance);

    sf::Vector2f avoidance(0.f, 0.f);
    for (const auto& other : enemy.GetSurroundingEnemies())
    {
        sf::Vector2f toOther = enemy.GetPosition() - other->GetPosition();
        float distance = Utility::magnitude(toOther.x, toOther.y);
        if (distance < 45.0f && distance > 0.01f)
        {
            toOther = Utility::unitVector2D(toOther);
            avoidance += toOther * (45.0f - distance);
			if (!startTimer)
				boatStuckTimer.restart();
            startTimer = true;
        }
        else {
			startTimer = false;
        }
    }

    sf::Vector2f finalMove = distance + avoidance * 0.1f;
    finalMove = Utility::unitVector2D(finalMove);

    distance = Utility::unitVector2D(distance);

    float tooClose = Utility::magnitude(finalMove.x, finalMove.y);
	if (tooClose < 0.1f)
	{
        path.clear();
        currentNodeInPath = 0;
        return;
	}

    enemy.SetPosition(enemy.GetPosition() + finalMove * 0.5f);
    enemy.UpdateDirection(distance);

}

std::shared_ptr<Node> EnemyBoatWander::SelectNextTarget(Enemy& enemy)
{
    auto possibleNodes = GetValidNodes(enemy);

    std::ranges::shuffle(possibleNodes.begin(), possibleNodes.end(), std::mt19937(std::random_device()()));

    return possibleNodes.front();
}

std::vector<std::shared_ptr<Node>> EnemyBoatWander::GetValidNodes(Enemy& enemy)
{
    std::vector<std::shared_ptr<Node>> waterNodes;
    std::vector<std::shared_ptr<Node>> landNodes;

    for (auto& node : enemy.getUpdateableArea()->getUpdateableNodes())
    {
        if (!node->getIsLand())
        {
            sf::Vector2f nodePos = node->getPosition();

            switch (enemy.GetDirection())
            {
            case NORTH:
                if (nodePos.y < enemy.getCurrentNode()->getPosition().y) waterNodes.push_back(node);
                break;
            case SOUTH:
                if (nodePos.y > enemy.getCurrentNode()->getPosition().y) waterNodes.push_back(node);
                break;
            case EAST:
                if (nodePos.x > enemy.getCurrentNode()->getPosition().x) waterNodes.push_back(node);
                break;
            case WEST:
                if (nodePos.x < enemy.getCurrentNode()->getPosition().x) waterNodes.push_back(node);
                break;
            }
        }else
        {
            landNodes.push_back(node);
        }
    }

    if(!landNodes.empty())
    {
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> goOnLand(1, 15); //1/15 to go onto land
        if (goOnLand(gen) == 1)
        {
            return landNodes;
        }
    }

    if (waterNodes.empty())
    {
        ChangeDirection(enemy);
        return GetValidNodes(enemy);
    }

    return waterNodes;
}

void EnemyBoatWander::ChangeDirection(Enemy& enemy)
{
    std::vector<EnemyDirection> possibleDirections;
    auto nodeSizeRef = enemy.getCurrentNode()->getNodeData().size;

    std::vector<std::pair<EnemyDirection, sf::Vector2f>> directions = {
        {NORTH, enemy.getCurrentNode()->getPosition() + sf::Vector2f(0,-nodeSizeRef)},
        {SOUTH, enemy.getCurrentNode()->getPosition() + sf::Vector2f(0,nodeSizeRef)},
        {EAST, enemy.getCurrentNode()->getPosition() + sf::Vector2f(nodeSizeRef, 0)},
        {WEST, enemy.getCurrentNode()->getPosition() + sf::Vector2f(-nodeSizeRef, 0)}
    };

    for (const auto& [dir, checkPos] : directions)
    {
        for (const auto& node : enemy.getUpdateableArea()->getUpdateableNodes())
        {
            if (!node->getIsLand() && node->getPosition() == checkPos)
            {
                possibleDirections.push_back(dir);
                break;
            }
        }
    }

    if (!possibleDirections.empty())
    {
        enemy.ChangeDirection(possibleDirections[rand() % possibleDirections.size()]);
    }
}
