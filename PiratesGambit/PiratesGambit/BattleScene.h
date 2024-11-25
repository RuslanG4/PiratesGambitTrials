#pragma once
#include "Includes.h"
#include "BattleGridNode.h"
#include"Player.h"

class BattleScene
{
public:
	BattleScene(const std::shared_ptr<Player>& _player) : playerRef(_player)
	{
		initialiseBattleGrid();
		initialiseStartArea();

		placeUnits();
	};

	void placeUnits();

	void update();
	void render(sf::RenderWindow& _win) const;

	void initialiseBattleGrid();
	void addNeighbours(int _currentNodeId) const;

	void initialiseStartArea();
private:
	std::vector<std::shared_ptr<BattleGridNode>> battleGrid;
	std::vector<std::shared_ptr<BattleGridNode>> startArea;

	std::shared_ptr<Player> playerRef;

	int nodeSize = 64;

	int rowAmount = 12;
	int colAmount = 20;
};

