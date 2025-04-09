#pragma once
#include "EnemyState.h"
#include "Player.h"

class FollowPlayerState :
    public EnemyState
{
public:
    FollowPlayerState(const std::shared_ptr<Player>& _playerRef) :  playerRef(_playerRef)
    {
        currentNodeInPath = 0;
    }
    // Inherited via EnemyState
    void Enter(Enemy& enemy) override;
    void Update(Enemy& enemy, float deltaTime) override;
    void Exit(Enemy& enemy) override;

    void FindNewPath(Enemy& enemy);
    void FollowLeader(Enemy& enemy);
private:
	//std::shared_ptr<Enemy> targetCaptain;
	std::shared_ptr<Node> targetNode;
    std::shared_ptr<Node> destinationNode;

    std::shared_ptr<Player> playerRef;
    std::vector<std::shared_ptr<Node>> path;
    int currentNodeInPath = 0;
    sf::Clock detectPlayerClock;

};

