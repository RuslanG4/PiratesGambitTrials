#pragma once
#include "Includes.h"
#include "BattleGridNode.h"
#include"Player.h"
#include"Enemy.h"
#include"Enums.h"
#include"Mouse.h"
#include"BattleActionUI.h"
#include"TacticsArmyUI.h"
#include "PathFindingFunctions.h"
#include "DamageCalculations.h"
#include "EnemyMoveConditions.h"
#include "ParticleManager.h"

class BattleScene
{
public:
	BattleScene(const std::shared_ptr<Player>& _player) : playerRef(_player)
	{
		UIInterface = std::make_unique<BattleActionUI>();
		tacticsArmyUI = std::make_unique<TacticsArmyUI>(_player->getArmy());

		attackIcon.setTexture(TextureManager::getInstance().getTexture("SWORD_ICON"));
		attackIcon.setScale(2, 2);
		attackIcon.setOrigin(16,16);

		initialiseBattleGrid();
		initialiseStartArea();

		placeUnits(playerRef->getArmy(), false);

		background.setTexture(TextureManager::getInstance().getTexture("background"));
	}

	void setEnemyRef(const std::shared_ptr<Enemy>& _enemy) { enemyRef = _enemy; }

	void placeUnits(const std::unique_ptr<Army>& _army, bool _isEnemy);

	std::shared_ptr<BattleGridNode> placeEnemyUnits(std::vector<std::shared_ptr<BattleGridNode>>& _gridArea, const std::shared_ptr<PirateUnit>& _unit);

	void update(float _dt);
	void render(const std::unique_ptr<sf::RenderWindow>& window) const;

	void updateNextTurn();

	void initialiseBattleGrid();
	void addNeighbours(int _currentNodeId) const;

	void createMoveableArea(const std::shared_ptr<PirateUnit>& _unit);
	void aStarPathFind(const std::shared_ptr<BattleGridNode>& _start, const std::shared_ptr<BattleGridNode>& end);

	bool projectileCollisionCheck();

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

	void clearArea(std::vector<int> _ids);
	static void clearNodeArea(std::vector<std::shared_ptr<BattleGridNode>>& _vector);

	void TriggerAttack();

	void EnemyTurn();

	void calculateDamage(const std::shared_ptr<PirateUnit>& _attacker, const std::shared_ptr<PirateUnit>& _defender);

	std::shared_ptr<PirateUnit> selectUnit(sf::Vector2f _mousePos);

	int getCurrentNodeID(sf::Vector2f _pos);

	std::vector<std::shared_ptr<PirateUnit>> ScanNearByUnits();
	std::shared_ptr<PirateUnit> PickUnitToAttack(const std::vector<std::shared_ptr<PirateUnit>>& _possibleUnits) const;

	int SelectNodeToWalkTo();
	int SelectAttackNodeToWalkTo(const std::vector<std::shared_ptr<PirateUnit>>& _possibleUnits) const;

private:
	std::vector<std::shared_ptr<BattleGridNode>> battleGrid;

	std::vector<std::shared_ptr<BattleGridNode>> startArea;
	std::vector<std::shared_ptr<BattleGridNode>> enemyStartArea;

	std::vector<int> walkableNodesIDs;

	//bug clicking on other enemy shows attack button

	std::vector<std::shared_ptr<BattleGridNode>> path;

	std::unique_ptr<BattleActionUI> UIInterface;

	std::unique_ptr<TacticsArmyUI> tacticsArmyUI;

	BattleState currentState = PREP;

	std::shared_ptr<PirateUnit> currentSelectedUnit;
	std::shared_ptr<PirateUnit> currentDefendingUnit;


	std::shared_ptr<Player> playerRef;
	std::shared_ptr<Enemy> enemyRef;

	sf::Vector2f offset{ 380,65 };

	sf::Sprite attackIcon;

	int nodeSize = 80;

	int rowAmount = 8;
	int colAmount = 14;

	int selectedNodeID;

	int currentHoverNodeID=0;

	int currentNodeInPath = 0;

	int oldPositionRef = 0;

	bool move{ false };
	bool newAreaSet{ false };

	bool canAttack{ false };
	bool hasAttacked = false;

	bool startEnemyTurnTimer{ false };
	sf::Clock enemyWaitTime;
	void WaitForTurn();
	int attackNode = -1;

	sf::Sprite background;
};

