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
	void SpawnPlayer();
	void SpawnBoat(const std::shared_ptr<Island>& _island);

	void SpawnEnemies();
	void SpawnTeam(int _chunkIndex, sf::Texture& _texture);

	void processKeyUp(sf::Event& t_event);

	void processKeys();

	void HandleMovement() const;

	std::shared_ptr<Node> FindCurrentNode(sf::Vector2f _position) const;
	void UpdatePlayerCurrentNode() const;
	void UpdateEnemiesCurrentNode() const;

	void transitionToBattleMode(const std::shared_ptr<Node>& _node);

	void interactWithObjects(const std::shared_ptr<Node>& _node);
	bool interactWithBuildings(const std::shared_ptr<Node>& _node);

	void transferInventoryItems();

	void updateVisableNodes();

	void UpdateEnemies(double _dt);

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

	std::weak_ptr<GameObject> currentObjectInteract;
	std::shared_ptr<Building> currentBuildingInteract;

	//battle scene
	BattleSceneTransition battleTransition;
	std::unique_ptr<BattleScene> battleScene;
	bool battle = false ;

	int mapSize = 5;

	int enemiesPerFrame = 5;
	int enemyIndex = 0;

	std::random_device rd;
};

