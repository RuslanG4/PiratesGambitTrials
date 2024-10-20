#include "Node.h"

void Node::updatePath(sf::Color _col)
{
	drawableNode.setFillColor(_col);
}

void Node::setType(NodeType _type)
{
	entropy = 0;
	nodeCostText.setString(std::to_string(entropy));
}

void Node::determineColor()
{
	/*switch(*m_possibleTiles.begin())
	{
	case WATER:
		drawableNode.setFillColor(sf::Color::Blue);
		break;
	case LAND:
		drawableNode.setFillColor(sf::Color::Green);
		break;
	case SAND:
		drawableNode.setFillColor(sf::Color::Yellow);
		break;
	}
	drawn = true;*/

	if(isWall)
	{
		drawableNode.setFillColor(sf::Color::Yellow);
	}else
	{
		drawableNode.setFillColor(sf::Color::Blue);
	}
}

void Node::updateNodeTypes(std::vector<NodeType> _surroundingTypes)
{

}

void Node::determineEntropy()
{
	entropy = m_possibleTiles.size();
	nodeCostText.setString(std::to_string(entropy));
}

void Node::determineTile()
{
	std::vector<std::pair<NodeType, double>> weightedTiles;
	double totalWeight = 0.0;
	NodeType selectedTile;
	if (m_possibleTiles.size() > 1) {

		// Add only possible tiles with their weights
		for (NodeType tile : m_possibleTiles) {
			double weight = tileWeights[tile];
			weightedTiles.push_back({ tile, weight });
			totalWeight += weight;
		}
		double randomWeight = (rand() / (float)RAND_MAX) * totalWeight;

		// Select a tile based on the random weight
		for (const auto& [tile, weight] : weightedTiles) {
			if (randomWeight < weight) {
				selectedTile = tile;
				break;
			}
			randomWeight -= weight;
		}
		m_possibleTiles = { selectedTile };
	}


	//int randomIndex;
	//if (m_possibleTiles.size() < 1) {
	//	randomIndex = 0;
	//}
	//else
	//{
	//	randomIndex = rand() % m_possibleTiles.size();
	//}
	//auto it = m_possibleTiles.begin();
	//std::advance(it, randomIndex);

	

	determineColor();
}




