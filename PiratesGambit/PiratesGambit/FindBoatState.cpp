#include "FindBoatState.h"

#include "Enemy.h"
#include "PathFindingFunctions.h"

void FindBoatState::Enter(Enemy& enemy)
{
    std::cout << "Enemy is entering find boat state." <<"\n";
    path = PathFindingFunctions<Node>::aStarPathFind(enemy.getCurrentNode(), enemy.GetBoat()->getDockedNode(), enemy.isOnBoat());
    int x = 0;
}

void FindBoatState::Update(Enemy& enemy, float deltaTime)
{
    if(!path.empty())
    {
        ChasePlayer(enemy);
    }else
    {
        enemy.boardBoat(enemy.GetBoat());
        enemy.ChangeState(new IdleState(playerRef));
    }
}

void FindBoatState::Exit(Enemy& enemy)
{
    std::cout << "Enemy is leaving find boat state." << "\n";
}

void FindBoatState::ChasePlayer(Enemy& enemy)
{
    if (currentNodeInPath >= path.size()) {
        path.clear();
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

    FacePath(enemy, distance);

    enemy.SetPosition(enemy.GetPosition() + distance);
}

void FindBoatState::FacePath(Enemy& enemy, sf::Vector2f distance)
{
    if (distance.x < 0)
    {
        enemy.FacePlayer(-2);
    }
    else
    {
        enemy.FacePlayer(2);
    }
}
