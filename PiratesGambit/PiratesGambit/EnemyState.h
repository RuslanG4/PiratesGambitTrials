#pragma once
#include"Includes.h"

class Enemy;
class EnemyBoat;

class EnemyState
{
public:
    virtual ~EnemyState() = default;

    virtual void Enter(Enemy& enemy) = 0;
    virtual void Update(Enemy& enemy, float deltaTime) = 0;
    virtual void Exit(Enemy& enemy) = 0;
};