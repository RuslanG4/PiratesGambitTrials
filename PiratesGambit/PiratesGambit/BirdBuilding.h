#pragma once
#include "Building.h"
class BirdBuilding :
    public Building
{
public:
    BirdBuilding(const std::shared_ptr<Player>& _playerRef);
private:
};

