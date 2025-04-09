#pragma once
#include "Enemy.h"
#include "FullMap.h"
#include "Scene.h"
#include "BattleScene.h"
#include "BattleSceneTransition.h"
#include "Player.h"
#include "Boat.h"
#include "EnemyBoat.h"
#include "PlayerTabMenu.h"
#include "Camera.h"
#include "UnitStatsDisplay.h"
#include"AllianceDialogueUI.h"
#include"EnemyScoutUI.h"
#include <fstream>
#include "json.hpp"
#include"FindBoatState.h"
#include"KeyPopUpManager.h"
#include"PauseScreen.h"

class PlayerTabMenu;

class GamePlayScene :
    public Scene
{
public:
	GamePlayScene();

	void handleInput(const std::unique_ptr<sf::RenderWindow>& window, sf::Event newEvent) override;
	void update(float dt) override;
	void render(const std::unique_ptr<sf::RenderWindow>& window) override;

private:
	void SpawnPlayer();
	void SpawnBoat(const std::shared_ptr<Island>& _island);

	void SpawnEnemies();
	void InitialiseEnemyArmy(const std::shared_ptr<Enemy>& _enemyRef, nlohmann::json& jsonData);
	void SpawnTeam(int _chunkIndex, const UnitAllegiance& _allegiance);

	void processKeyUp(sf::Event& t_event);

	void processKeys();

	void HandleEnemyScoutUI(const std::unique_ptr<sf::RenderWindow>& window);

	void HandleMovement() const;

	void HandlePauseScreen();

	void HandleProjectiles();
	void RemoveEnemy();

	std::shared_ptr<Node> FindCurrentNode(sf::Vector2f _position) const;
	void UpdatePlayerCurrentNode() const;
	void UpdateEnemiesCurrentNode();

	void LookForSurroundingEnemies(const std::shared_ptr<Enemy>& enemy);

	void transitionToBattleMode(const std::shared_ptr<Node>& _node);

	void interactWithObjects(const std::shared_ptr<Node>& _node);
	bool interactWithBuildings(const std::shared_ptr<Node>& _node);
	void handleKeyPopUps();

	void transferInventoryItems();

	void updateVisableNodes();

	void UpdateEnemies(double _dt);

	int FindCurrentTeamSize(nlohmann::json& jsonData, const UnitAllegiance& _allegiance);

	std::set<int> visibleNodes;

	bool keyUp = true;
	bool interactWithObject = false;

	std::set<Node*> updateArea{ nullptr };

	Node* currentNode;

	std::shared_ptr<Island> currentIsland;

	std::unique_ptr<FullMap> myMap;
	std::shared_ptr<Player> myPlayer;
	std::unique_ptr<PlayerTabMenu> playerMenu;
	std::shared_ptr<Boat> playerBoat;

	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<EnemyBoat>> enemyBoats;
	//std::shared_ptr<Enemy> enemy;
	//std::shared_ptr<EnemyBoat> enemyBoat;

	std::shared_ptr<GameObject> currentObjectInteract;
	std::shared_ptr<Building> currentBuildingInteract;

	//battle scene
	BattleSceneTransition battleTransition;
	std::unique_ptr<BattleScene> battleScene;
	bool battle = false;
	bool previousEscapePressed = false;

	int mapSize = 3;

	int enemiesPerFrame = 5;
	int enemyIndex = 0;

	std::random_device rd;
};

