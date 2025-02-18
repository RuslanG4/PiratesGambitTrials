#include "Island.h"

void Island::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	for(auto& node:landNodes)
	{
		//window->draw(*(node->debugShape));
	}
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
		if (gameObject->getInventory()->isInventoryOpen())
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
		gameObject->update();
	}
}

void Island::GenerateTrees(int _clumps)
{
	for(int i =0; i< _clumps; i++)
	{
		std::vector<std::shared_ptr<Node>> PossibleNodes = PoissonDiskSampling::generateObjects(landNodes, 5);

		for (size_t i = 0; i < PossibleNodes.size(); ++i)
		{
			gameObjects.push_back(std::make_shared<Tree>());
			PossibleNodes[i]->updateOccupied(true);
			gameObjects.back()->setPosition(PossibleNodes[i]->getMidPoint());
		}
	}
	std::ranges::sort(gameObjects, [](const std::shared_ptr<GameObject>& obj1, const std::shared_ptr<GameObject>& obj2) {
		return obj1->GetPosition().y < obj2->GetPosition().y;
		});
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
	for (int i = 0; i < buildingCount; i++) {
		std::vector<std::shared_ptr<Node>> TownArea;

		int attempts = 0;
		const int maxAttempts = 100;

		while (TownArea.size() < 20 && attempts < maxAttempts) {
			attempts++;
			std::shared_ptr<Node> startNode = landNodes[rand() % landNodes.size()];
			// Find a valid start node if the current one is not LAND
			while (startNode->getParentTileType() != LAND && startNode->IsInBuildingArea() && attempts < maxAttempts) {
				startNode = landNodes[rand() % landNodes.size()];
			}

			UnmarkNodes();
			TownArea = PathFindingFunctions<Node>::BreathSearchEuclydianIslands(startNode, 2);
			
		}

		// If attempts reached maxAttempts, the loop will exit
		if (TownArea.size() < 20) {
			// Handle failure case here (e.g., logging, default fallback, etc.)
			std::cout << "Failed to generate town area within 100 attempts.";
		}
		else {
			bool placed = false;
			for (auto& node : TownArea)
			{
				node->UpdateIsBuildingArea(true);
				bool allNeighboursAreLand = std::ranges::all_of(node->getNeighbours(),
					[](const auto& neighbour) {
						return neighbour.first->getParentTileType() == LAND;
					});

				if (allNeighboursAreLand && !placed) {
					auto building = std::make_shared<GunnerBuilding>(playerRef);
					building->SetPosition(node->getMidPoint());
					Mark3x3Area(node);
					buildings.push_back(std::move(building));
					placed = true;
				}

			}
			MarkNodes();
		}
	}

	
	GenerateTrees(5);
}

void Island::Mark3x3Area(const std::shared_ptr<Node>& _startNode) const
{
	_startNode->updateOccupied(true);
	for(auto& neighbour : _startNode->getNeighbours())
	{
		neighbour.first->updateOccupied(true);
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


