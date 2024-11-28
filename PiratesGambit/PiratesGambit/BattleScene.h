#pragma once
#include "Includes.h"
#include "BattleGridNode.h"
#include"Player.h"
#include"Enums.h"
#include"Mouse.h"

class BattleScene
{
public:
	class Compare {
	public:
		bool operator()(const std::shared_ptr<BattleGridNode>& a, const std::shared_ptr<BattleGridNode>& b) {
			// Compare based on the total estimated cost (f cost)
			if (a->getNodeData().fCost == b->getNodeData().fCost) {
				// Use h cost as a tiebreaker
				return a->getNodeData().hCost > b->getNodeData().hCost;
			}
			return a->getNodeData().fCost > b->getNodeData().fCost;
		}
	};

	BattleScene(const std::shared_ptr<Player>& _player) : playerRef(_player)
	{
		initialiseBattleGrid();
		initialiseStartArea();

		placeUnits();
	};

	void placeUnits();

	void update(float _dt);
	void render(sf::RenderWindow& _win) const;

	void initialiseBattleGrid();
	void addNeighbours(int _currentNodeId) const;

	void createMoveableArea(const std::unique_ptr<PirateUnit>& _unit);
	void aStarPathFind(const std::shared_ptr<BattleGridNode>& _start, const std::shared_ptr<BattleGridNode>& end);
	void createVectors(const std::shared_ptr<BattleGridNode>& end);

	void initialiseStartArea();

	void detectMouse();

	void moveUnit(const std::unique_ptr<PirateUnit>& _unit);

	int getCurrentNodeID(sf::Vector2f _pos);
private:
	std::vector<std::shared_ptr<BattleGridNode>> battleGrid;
	std::vector<std::shared_ptr<BattleGridNode>> startArea;

	std::vector<std::shared_ptr<BattleGridNode>> walkableNodes;

	std::vector<std::shared_ptr<BattleGridNode>> path;

	BattleState currentState = PREP;

	std::shared_ptr<Player> playerRef;

	sf::Vector2f offset{ 300,200 };

	int nodeSize = 64;

	int rowAmount = 12;
	int colAmount = 14;

	int selectedNodeID;

	int currentNodeInPath = 0;

	bool move{ false };
};

