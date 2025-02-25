#include "Island.h"

void Island::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	//for(auto& node:landNodes)
	//{
	//	window->draw(*(node->debugShape));
	//}
	for (const auto& building : buildings)
	{
		building->Render(window);  // Draw buildings with camera view
	}
	for (auto& gameObject : gameObjects)
	{
		gameObject->render(window);
	}
	// Render UI after the game objects (building sprites)
	for (const auto& building : buildings)
	{
		building->RenderUI(window);  // Draw UI elements on top
	}
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->getInventory()->IsPersonalOpen())
		{
			gameObject->RenderUI(window);
		}
	}
}

void Island::update(float _dt) const
{
	for(auto& gameObject : buildings)
	{
		gameObject->Update(_dt);
	}
	for (auto& gameObject : gameObjects)
	{
		gameObject->update(_dt);
	}
}

void Island::GenerateIsland()
{
	std::vector<std::shared_ptr<Node>> validNodes = landNodes;

	GenerateTrees(validNodes);
	validNodes = landNodes;
	GenerateBuildings(3, validNodes);
	validNodes = landNodes;
	GenerateBarrels(validNodes);
	MarkNodes(); //for other chunks

	std::ranges::sort(gameObjects, [](const std::shared_ptr<GameObject>& obj1, const std::shared_ptr<GameObject>& obj2) {
		return obj1->GetPosition().y < obj2->GetPosition().y;
		});
}

void Island::GenerateTrees(std::vector<std::shared_ptr<Node>>& _nodes)
{
	int totalTrees = CalculateTreeCount(_nodes.size());

	std::vector<int> clumps = DistributeTreesIntoClumps(totalTrees);

	for(int clump : clumps)
	{
		std::vector<std::shared_ptr<Node>> PossibleNodes = ObjectPlacement::placeTrees(_nodes, clump);

		for(auto &node: PossibleNodes)
		{
			gameObjects.push_back(std::make_shared<Tree>());
			node->updateOccupied(true);
			gameObjects.back()->setNodeId(node->getID());
			gameObjects.back()->setPosition(node->getMidPoint());
		}
	}

	ClearIslandNodeConditions();
	MarkAreaAroundTrees();
}

void Island::MarkAreaAroundTrees()
{
	for (auto& gameObject : gameObjects) {
		auto it = std::ranges::find_if(landNodes, [&gameObject](const std::shared_ptr<Node>& node) {
			return node->getID() == gameObject->getID();
			});

		if (it != landNodes.end()) {
			auto& node = *it;
			for (auto& neighbour : node->getNeighbours()) {
				neighbour.first->UpdateIsBuildingArea(true);
				//neighbour.first->debugShape->setFillColor(sf::Color::Red);
			}
		}
	}

}

void Island::GenerateBarrels(std::vector<std::shared_ptr<Node>>& _nodes)
{
	int totalBarrels = CalculateBarrelCount(_nodes.size());

	for(int i =0; i< totalBarrels; i++)
	{
		auto node = ObjectPlacement::placeBarrel(_nodes);

		if (node) {
			gameObjects.push_back(std::make_shared<Barrel>());
			node->updateOccupied(true);
			gameObjects.back()->setNodeId(node->getID());
			gameObjects.back()->setPosition(node->getMidPoint());
		}
	}

}

int Island::CalculateTreeCount(int landNodes)
{
	if (landNodes < 30) return 0;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dist(0.08, 0.12); 

	int treeCount = static_cast<int>(landNodes * dist(gen));
	return treeCount;
}


std::vector<int> Island::DistributeTreesIntoClumps(int totalTrees)
{
	if (totalTrees < 5) return {}; // Not enough trees for a valid clump

	std::random_device rd;
	std::mt19937 gen(rd());

	std::vector<int> clumps;
	int remainingTrees = totalTrees;

	while (remainingTrees >= 5) {
		int clumpSize = std::min(remainingTrees, std::uniform_int_distribution<int>(3, 5)(gen));
		clumps.push_back(clumpSize);
		remainingTrees -= clumpSize;
	}

	// If there are leftover trees (1-4), distribute them to existing clumps
	for (int i = 0; remainingTrees > 0 && i < clumps.size(); ++i) {
		if (clumps[i] < 7) {
			clumps[i]++;
			remainingTrees--;
		}
	}

	return clumps;
}

int Island::CalculateBarrelCount(int islandSize)
{
	const int minBarrels = 1;
	const int maxBarrels = 4;

	const int minIslandSize = 50;  
	const int maxIslandSize = 500; 

	islandSize = std::max(minIslandSize, std::min(islandSize, maxIslandSize));

	// Calculate the barrel count based on the island size, mapped to 1-4 range
	double barrelRatio = static_cast<double>(islandSize - minIslandSize) / (maxIslandSize - minIslandSize);
	int barrelCount = static_cast<int>(minBarrels + barrelRatio * (maxBarrels - minBarrels));

	return barrelCount;
}


void Island::UnmarkNodes()
{
	for(auto& node : landNodes)
	{
		node->updateTraversed(false);
	}
}

void Island::MarkNodes()
{
	for (auto& node : landNodes)
	{
		node->updateTraversed(true);
	}
}

void Island::ClearIslandNodeConditions()
{
	for (auto& node : landNodes)
	{
		node->UpdateIsBuildingArea(false);
	}
}

void Island::GenerateBuildings(int buildingCount, std::vector<std::shared_ptr<Node>>& _nodes)
{
	for (int i = 0; i < buildingCount; i++) {
		std::vector<std::shared_ptr<Node>> TownArea;
		std::shared_ptr<Node> startNode = nullptr;

		int attempts = 0;
		const int maxAttempts = 100;

		while (!_nodes.empty() && attempts < maxAttempts)
		{
			int randomIndex = rand() % _nodes.size();
			startNode = _nodes[randomIndex];

			if (startNode->getParentTileType() == LAND && !startNode->IsInBuildingArea()) {
				UnmarkNodes();
				TownArea = PathFindingFunctions<Node>::BreathSearchEuclydianIslands(startNode, 3);

				if (TownArea.size() >= 17) {
					break;
				}
			}

			_nodes.erase(_nodes.begin() + randomIndex);
			attempts++;
		}

		if (TownArea.size() < 17) {
			std::cout << "Failed to generate town area within 100 attempts.\n";
			TownArea.clear();
			continue; 
		}
		
			bool placed = false;
			for (auto& node : TownArea)
			{
				//node->debugShape->setFillColor(sf::Color::Blue);
				node->UpdateIsBuildingArea(true);
				if (!placed) {
					auto building = std::make_shared<GunnerBuilding>(playerRef);
					building->SetPosition(node->getMidPoint());
					Mark3x3Area(node, building);
					buildings.push_back(std::move(building));
					placed = true;
				}

			}

	}
}

void Island::Mark3x3Area(const std::shared_ptr<Node>& _startNode, const std::shared_ptr<Building>& _building) const
{
	_startNode->updateOccupied(true);
	_building->AddParentNode(_startNode);
	for(auto& neighbour : _startNode->getNeighbours())
	{
		neighbour.first->updateOccupied(true);
		_building->AddToOccupiedNodes(neighbour.first->getID());
	}
}

void Island::PlaceEnemy(const std::shared_ptr<Enemy>& _enemy)
{
	for (auto& node : landNodes)
	{
		if (!node->isOccupied())
		{
			_enemy->updatePosition(node->getMidPoint());
			break;
		}
	}
}


