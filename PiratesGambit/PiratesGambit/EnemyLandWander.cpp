#include "EnemyLandWander.h"

#include "ChaseState.h"
#include "Enemy.h"
#include "PathFindingFunctions.h"

void EnemyLandWander::Enter(Enemy& enemy)
{
    std::cout << "Enemy is entering land wander state." << "\n";
    enemy.SetAnimationState(UnitState::WALK);
}

void EnemyLandWander::Update(Enemy& enemy, float deltaTime)
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
    }
    if (path.empty()) {
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 5); //20% chance for idle
        if (dis(gen) == 1) {
            enemy.ChangeState(new IdleState(playerRef));  
        }
        else {
            targetNode = SelectNextTarget(enemy);
            path = PathFindingFunctions<Node>::aStarPathFind(enemy.getCurrentNode(), targetNode, enemy.isOnBoat());
        }
    }

    MoveTowardsTarget(enemy);
}

void EnemyLandWander::Exit(Enemy& enemy)
{
    std::cout << "Enemy is exiting land wander state." << "\n";
}

void EnemyLandWander::MoveTowardsTarget(Enemy& enemy)
{
    if (currentNodeInPath >= path.size()) {
        path.clear();
        return;
    }

    sf::Vector2f distance = path[currentNodeInPath]->getMidPoint() - enemy.GetPosition();
    float magnitude = Utility::magnitude(distance.x, distance.y);

    if (magnitude < 2.0f) {
        currentNodeInPath++;

        if (currentNodeInPath >= path.size()) {
            path.clear();
            currentNodeInPath = 0;
            return;
        }
        distance = path[currentNodeInPath]->getMidPoint() - enemy.GetPosition();
    }

    distance = Utility::unitVector2D(distance);

    enemy.FaceDirection(distance);
    enemy.SetPosition(enemy.GetPosition() + distance * 0.5f);
}

std::shared_ptr<Node> EnemyLandWander::SelectNextTarget(Enemy& enemy)
{
    std::vector<std::shared_ptr<Node>> possibleNodes;

    for(auto& node : enemy.getUpdateableArea()->getUpdateableNodes())
    {
	    if(node->getIsLand() && !node->isOccupied())
	    {
            possibleNodes.push_back(node);
	    }
    }

    std::ranges::shuffle(possibleNodes.begin(), possibleNodes.end(), std::mt19937(std::random_device()()));

    return possibleNodes.front();
}
