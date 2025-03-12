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
	void processKeys(sf::Event t_event);
	void processKeyUp(sf::Event t_event);

	void FindCurrentChunk();
	void FindCurrentIsland();

	void FindCurrentNodeInSameChunk(int _id, const std::shared_ptr<Enemy>& _enemy) const;

	void FindCurrentNode() const;
	void FindPlayerCurrentNode() const;
	void FindEnemyCurrentNode(const std::shared_ptr<Enemy>& _enemy) const;

	void HandleGameObjectCollision();
	void HandleBuildingCollision();

	void handleKeyInput();

	void transitionToBattleMode();

	void interactWithObjects();
	bool interactWithBuildings();

	void transferInventoryItems();

	void updateVisableNodes();

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

	std::shared_ptr<Enemy> enemy;
	std::shared_ptr<EnemyBoat> enemyBoat;

	std::weak_ptr<GameObject> currentObjectInteract;
	std::shared_ptr<Building> currentBuildingInteract;

	//battle scene
	BattleSceneTransition battleTransition;
	std::unique_ptr<BattleScene> battleScene;
	bool battle = false ;

	int mapSize = 1;


};

