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
#include"EndBattleUI.h"
#include"FloatingNumber.h"

class BattleScene
{
public:
	BattleScene(const std::shared_ptr<Player>& _player) : playerRef(_player)
	{
		UIInterface = std::make_unique<BattleActionUI>();
		tacticsArmyUI = std::make_unique<TacticsArmyUI>(_player->getArmy());
		endBattleUI = std::make_unique<EndBattleUI>();

		playerArmyDead = std::make_unique<Army>();
		enemyArmyDead = std::make_unique<Army>();

		attackIcon.setTexture(TextureManager::getInstance().getTexture("SWORD_ICON"));
		attackIcon.setScale(2, 2);
		attackIcon.setOrigin(16,16);

		background.setTexture(TextureManager::getInstance().getTexture("background"));
	}
	void endBattle();
	void resetBattle();
	bool isBattleOver() const { return endBattleUI->isOKClicked(); }
	bool isPlayerWin() const { return endBattleUI->isPlayerWin(); }
	void handleEvent(const sf::Event& event);

	void setEnemyRef(const std::shared_ptr<Enemy>& _enemy) { enemyRef = _enemy; }

	void placeUnits(const std::unique_ptr<Army>& _army, bool _isEnemy);

	std::shared_ptr<BattleGridNode> placeEnemyUnits(std::vector<std::shared_ptr<BattleGridNode>>& _gridArea, const std::shared_ptr<PirateUnit>& _unit);

	void update(float _dt);
	void render(const std::unique_ptr<sf::RenderWindow>& window) const;

	bool updateNextTurn();

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
	void searchNeighboursToAttack();

	void preGameStartUpPlacement(sf::Vector2f _mousePos);

	void clearArea(std::vector<int> _ids);
	static void clearNodeArea(std::vector<std::shared_ptr<BattleGridNode>>& _vector);

	void TriggerAttack();

	void SkipTurn();
	void EnemyTurn();

	void calculateDamage(const std::shared_ptr<PirateUnit>& _attacker, const std::shared_ptr<PirateUnit>& _defender);
	void assignDeadUnits(const std::shared_ptr<PirateUnit>& _defender, int _amount);
	void pickPerciseUnit(const std::shared_ptr<PirateUnit>& _defender, const std::unique_ptr<Army>& _ref, int _amount);

	std::shared_ptr<PirateUnit> selectUnit(sf::Vector2f _mousePos);

	int getCurrentNodeID(sf::Vector2f _pos);

	std::vector<std::shared_ptr<PirateUnit>> ScanNearByUnits();
	std::shared_ptr<PirateUnit> PickUnitToAttack(const std::vector<std::shared_ptr<PirateUnit>>& _possibleUnits) const;

	int SelectNodeToWalkTo();
	int SelectAttackNodeToWalkTo(const std::vector<std::shared_ptr<PirateUnit>>& _possibleUnits);

	bool CheckBattleOver(const std::unique_ptr<Army>& _army);
	void AddCoinsToPlayer();
	void RemoveDeadUnits();

	const std::shared_ptr<Enemy>& getEnemyRef() const { return enemyRef; }	

private:
	std::vector<std::shared_ptr<BattleGridNode>> battleGrid;

	std::vector<std::shared_ptr<BattleGridNode>> startArea;
	std::vector<std::shared_ptr<BattleGridNode>> enemyStartArea;

	std::vector<std::unique_ptr<FloatingNumber>> floatingNumbers;

	std::vector<int> walkableNodesIDs;

	//bug clicking on other enemy shows attack button

	std::vector<std::shared_ptr<BattleGridNode>> path;

	std::unique_ptr<EndBattleUI> endBattleUI;

	std::unique_ptr<BattleActionUI> UIInterface;

	std::unique_ptr<TacticsArmyUI> tacticsArmyUI;

	BattleState currentState = PREP;

	std::shared_ptr<PirateUnit> currentSelectedUnit;
	std::shared_ptr<PirateUnit> currentDefendingUnit;

	std::unique_ptr<Army> playerArmyDead;
	std::unique_ptr<Army> enemyArmyDead;

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
	float turnWaitTime = 1.f;
	void WaitForTurn();
	int attackNode = -1;

	sf::Sprite background;

	bool startUnit{ false };
	bool scanForAttack{ false };

	bool removeUnitAnimation = false;
	std::shared_ptr<PirateUnit> unitToRemove;
	std::shared_ptr<PirateUnit> lastAttackedUnit;

	bool showEndGame{ false };
	sf::Clock endGameTimer;
	void WaitForEndGameTimer();

};

