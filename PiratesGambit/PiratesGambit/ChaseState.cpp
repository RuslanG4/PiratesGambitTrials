#include "ChaseState.h"

#include "Enemy.h"
#include "FindBoatState.h"
#include "IdleState.h"
#include "PathFindingFunctions.h"

void ChaseState::Enter(Enemy& enemy)
{
    std::cout << "Enemy is entering chase state." << std::endl;
    enemy.SetAnimationState(UnitState::WALK);
    detectPlayerClock.restart();
    FindNewPath(enemy);
}

void ChaseState::Update(Enemy& enemy, float deltaTime)
{
    if (detectPlayerClock.getElapsedTime().asSeconds() >= 1.0f)
    {
        FindNewPath(enemy);

        if (enemy.GetCurrentState() != this) return;
    }

    if (!path.empty()) {
        ChasePlayer(enemy);
    }
    else
    {
        enemy.ChangeState(new IdleState(playerRef));
    }
}

void ChaseState::Exit(Enemy& enemy)
{
    std::cout << "Enemy is leaving chase state.";
}

void ChaseState::FindNewPath(Enemy& enemy)
{
    path.clear();

    if (!enemy.getUpdateableArea()) return;

    for (auto& node : enemy.getUpdateableArea()->getUpdateableNodes())
    {
        if (!playerRef->isOnBoat())
        {
            if (node == playerRef->getCurrentNode())
            {
                if (enemy.isOnBoat()) {
                    path = PathFindingFunctions<Node>::generalAStarPathFind(enemy.getCurrentNode(), playerRef->getCurrentNode());
                }
                else {
                    path = PathFindingFunctions<Node>::aStarPathFind(enemy.getCurrentNode(), playerRef->getCurrentNode(), enemy.isOnBoat());
                } 
                currentNodeInPath = 0;
                break;
            }
        }
        else if (playerRef->isOnBoat() && enemy.isOnBoat())
        {
            path = PathFindingFunctions<Node>::aStarPathFind(enemy.getCurrentNode(), playerRef->getCurrentNode(), enemy.isOnBoat());
            currentNodeInPath = 0;
            break;
        }
        else if (playerRef->isOnBoat() && !enemy.isOnBoat())
        {
            enemy.ChangeState(new FindBoatState(playerRef));
            break;
        }
    }

    detectPlayerClock.restart(); // Restart the clock **after** finding a new path
}

void ChaseState::ChasePlayer(Enemy& enemy)
{
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

    if (magnitude < 2.0f) {
        currentNodeInPath++;

        // Ensure we don't go out of bounds
        if (currentNodeInPath >= path.size()) {
            path.clear();
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
        if (distance < 30.0f && distance > 0.01f)
        {
            toOther = Utility::unitVector2D(toOther);
            avoidance += toOther * (30.0f - distance); 
        }
    }

    sf::Vector2f finalMove = distance + avoidance * 0.1f;
    finalMove = Utility::unitVector2D(finalMove);

    enemy.FaceDirection(distance);

    enemy.SetPosition(enemy.GetPosition() + finalMove);
}


