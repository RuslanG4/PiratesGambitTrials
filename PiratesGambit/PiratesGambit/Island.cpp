#include "Island.h"

void Island::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
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

bool Island::CanPlaceObject()
{
	return false;
}

void Island::PlaceBuildings(const std::shared_ptr<Node>& _startNode, int range)
{
	UnmarkNodes();

	std::vector<std::shared_ptr<Node>> PossibleNodes = DiskSampling::BreathFindNodes(landNodes, _startNode, range);

	while (!PossibleNodes.empty())
	{
		// Select a random index
		int randomIndex = rand() % PossibleNodes.size();
		auto node = PossibleNodes[randomIndex];

		// Remove the selected node from the list to avoid duplicate checks
		PossibleNodes.erase(PossibleNodes.begin() + randomIndex);

		if (allNeighboursAreLand(node))
		{
			buildings[currentBuildingIndex]->SetPosition(node->getMidPoint());
			buildings[currentBuildingIndex]->AddToOccupiedNodes(node->getID());
			buildings[currentBuildingIndex]->AddParentNode(node);
			node->updateOccupied(true);

			for (auto& neighbourNode : node->getNeighbours() | std::views::keys)
			{
				buildings[currentBuildingIndex]->AddToOccupiedNodes(neighbourNode->getID());
				neighbourNode->updateOccupied(true);
			}


			auto currentBuilding = buildings[currentBuildingIndex];

			currentBuildingIndex++;

			if (currentBuildingIndex >= buildings.size())
			{
				break;
			}

			PlaceBuildings(currentBuilding->GetParentNode(), range);

			break;
		}
	}

}

void Island::PlaceBarrels()
{
	bool condition = false;
	for (auto& node : landNodes)
	{
		if (node->getParentTileType() == LAND && !node->isOccupied())
		{
			for(auto& object : gameObjects)
			{
				object->setPosition(node->getMidPoint());
				object->setNodeId(node->getID());
				node->updateOccupied(true);
				condition = true;
				break;
			}
		}
		if (condition)
		{
			break;
		}
	}
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

bool Island::allNeighboursAreLand(const std::shared_ptr<Node>& node)
{
	int parentTileType = node->getParentTileType();

	return std::ranges::all_of(node->getNeighbours(), [parentTileType](const auto& neighbour) {
		return neighbour.first->getParentTileType() == parentTileType;
		});
}
