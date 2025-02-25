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
			gameObjects.back()->setPosition(node->getMidPoint());
		}
	}

	GenerateBarrels(_nodes);

	std::ranges::sort(gameObjects, [](const std::shared_ptr<GameObject>& obj1, const std::shared_ptr<GameObject>& obj2) {
		return obj1->GetPosition().y < obj2->GetPosition().y;
		});
}

void Island::GenerateBarrels(std::vector<std::shared_ptr<Node>>& _nodes)
{
	int totalBarrels = CalculateBarrelCount(_nodes.size());

	for(int i =0; i< 2; i++)
	{
		auto node = ObjectPlacement::placeBarrel(_nodes);

		gameObjects.push_back(std::make_shared<Barrel>());
		node->updateOccupied(true);
		gameObjects.back()->setNodeId(node->getID());
		gameObjects.back()->setPosition(node->getMidPoint());
	}

}

int Island::CalculateTreeCount(int landNodes)
{
	if (landNodes < 30) return 0;  // No trees if island is too small
	if (landNodes > 1000) landNodes = 1000;  // Cap at 1000 land nodes

	// Adjust the density factor based on the size of the island
	double densityFactor = 0.20 * (1.0 - (landNodes - 30) / 970.0);
	int treeCount = static_cast<int>(landNodes * densityFactor);

	// Ensure tree count doesn't exceed 25% of the land nodes
	treeCount = std::min(treeCount, static_cast<int>(landNodes * 0.25));

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
		int clumpSize = std::min(remainingTrees, std::uniform_int_distribution<int>(4, 7)(gen));
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
	// Minimum and maximum barrel count
	const int minBarrels = 1;
	const int maxBarrels = 4;

	// Set the thresholds for island sizes
	const int minIslandSize = 50;  // Size below which 1 barrel is placed
	const int maxIslandSize = 500; // Size above which 4 barrels can be placed

	// Clamp island size to be between minIslandSize and maxIslandSize
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

void Island::GenerateBuildings(int buildingCount)
{
	std::vector<std::shared_ptr<Node>> validLandNodes = landNodes;
	std::vector<std::shared_ptr<Node>> remainingNodes = landNodes;
	for (int i = 0; i < buildingCount; i++) {
		std::vector<std::shared_ptr<Node>> TownArea;
		std::shared_ptr<Node> startNode = nullptr;

		int attempts = 0;
		const int maxAttempts = 100;

		while (!validLandNodes.empty() && attempts < maxAttempts)
		{
			int randomIndex = rand() % validLandNodes.size();
			startNode = validLandNodes[randomIndex];

			if (startNode->getParentTileType() == LAND && !startNode->IsInBuildingArea()) {
				UnmarkNodes();
				TownArea = PathFindingFunctions<Node>::BreathSearchEuclydianIslands(startNode, 2);

				if (TownArea.size() >= 30) {
					break;
				}
			}

			validLandNodes.erase(validLandNodes.begin() + randomIndex);
			attempts++;
		}

		if (TownArea.size() < 30) {
			std::cout << "Failed to generate town area within 100 attempts.\n";
			TownArea.clear();
			continue; 
		}

			bool placed = false;
			for (auto& node : TownArea)
			{
				node->UpdateIsBuildingArea(true);
				node->debugShape->setFillColor(sf::Color::Red);
				bool allNeighboursAreLand = std::ranges::all_of(node->getNeighbours(),
					[](const auto& neighbour) {
						return neighbour.first->getParentTileType() == LAND;
					});

				if (allNeighboursAreLand && !placed) {
					auto building = std::make_shared<GunnerBuilding>(playerRef);
					building->SetPosition(node->getMidPoint());
					Mark3x3Area(node, building);
					buildings.push_back(std::move(building));
					placed = true;
				}

			}

			std::erase_if(remainingNodes, [&](const std::shared_ptr<Node>& node) {
				return std::ranges::any_of(TownArea, [&](const std::shared_ptr<Node>& townNode) {
					return node == townNode;
					});
				});
	}


	GenerateTrees(remainingNodes);


	MarkNodes();
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
		if (node->getParentTileType() == LAND && !node->isOccupied())
		{
			_enemy->updatePosition(node->getMidPoint());
			break;
		}
	}
}


