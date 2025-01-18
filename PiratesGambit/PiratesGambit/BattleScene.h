#pragma once
#include "Includes.h"
#include "BattleGridNode.h"
#include"Player.h"
#include"Enemy.h"
#include"Enums.h"
#include"Mouse.h"
#include"BattleActionUI.h"
#include"TacticsArmyUI.h"

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

	BattleScene(const std::shared_ptr<Player>& _player, const std::shared_ptr<Enemy>& _enemy) : playerRef(_player), enemyRef(_enemy)
	{
		UIInterface = std::make_unique<BattleActionUI>();
		tacticsArmyUI = std::make_unique<TacticsArmyUI>(_player->getArmy());

		attackIcon.setTexture(TextureManager::getInstance().getTexture("SWORD_ICON"));
		attackIcon.setScale(2, 2);
		attackIcon.setOrigin(16,16);

		initialiseBattleGrid();
		initialiseStartArea();

		placeUnits(playerRef->getArmy(), false);
	};

	void placeUnits(const std::unique_ptr<Army>& _army, bool _isEnemy) const;

	void update(float _dt);
	void render(const std::unique_ptr<sf::RenderWindow>& window) const;

	void initialiseBattleGrid();
	void addNeighbours(int _currentNodeId) const;

	void createMoveableArea(const std::shared_ptr<PirateUnit>& _unit);
	void aStarPathFind(const std::shared_ptr<BattleGridNode>& _start, const std::shared_ptr<BattleGridNode>& end);
	void createVectors(const std::shared_ptr<BattleGridNode>& end);

	void initialiseStartArea();

	void detectMouse();

	void TakeUnitAction(const std::shared_ptr<BattleGridNode>& _targetNode);

	void hoverMouseOnNode();
	void pinpointMousePosition(sf::Vector2f _mousePos, const std::shared_ptr<BattleGridNode>& _currentNode);
	void adjustAttackIcon(int _pinPointID);

	bool isNodeInRangeOfUnit();

	void moveUnit();
	void finalizeMoveUnit();

	void preGameStartUpPlacement(sf::Vector2f _mousePos);

	void clearStartArea();

	void EnemyTurn();

	std::shared_ptr<PirateUnit> selectUnit(sf::Vector2f _mousePos);

	int getCurrentNodeID(sf::Vector2f _pos);
private:
	std::vector<std::shared_ptr<BattleGridNode>> battleGrid;

	std::vector<std::shared_ptr<BattleGridNode>> startArea;
	std::vector<std::shared_ptr<BattleGridNode>> enemyStartArea;

	std::vector<std::shared_ptr<BattleGridNode>> walkableNodes;

	//bug clicking on other enemy shows attack button

	std::vector<std::shared_ptr<BattleGridNode>> path;

	std::unique_ptr<BattleActionUI> UIInterface;

	std::unique_ptr<TacticsArmyUI> tacticsArmyUI;

	BattleState currentState = PREP;

	std::shared_ptr<PirateUnit> currentSelectedUnit;

	std::shared_ptr<Player> playerRef;
	std::shared_ptr<Enemy> enemyRef;

	sf::Vector2f offset{ 450,50 };

	sf::Sprite attackIcon;

	int nodeSize = 80;

	int rowAmount = 8;
	int colAmount = 14;

	int selectedNodeID;

	int currentHoverNodeID=0;

	int currentNodeInPath = 0;

	int oldPositionRef = 0;

	bool clickedUnit{false};

	bool move{ false };
	bool newAreaSet{ false };

	bool rangedIcon{ false };

	bool canAttack{ false };
	int attackNode = -1;
};

