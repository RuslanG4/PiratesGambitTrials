#include "Node.h"

void Node::determineColor()
{
	switch(m_currentTileType)
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
}

void Node::noiseColor()
{
	if (isWall)
	{
		drawableNode.setFillColor(sf::Color::Yellow);
	}
	else
	{
		drawableNode.setFillColor(sf::Color::Blue);
	}
}

void Node::determineTile()
{
	bool hasWaterNeighbour{false};
	bool hasSandNeighbour{ false };

	for(auto neighbour: m_neighbours)
	{
		if(neighbour->m_currentTileType == TileType::WATER)
		{
			hasWaterNeighbour = true;
		}
		else if(neighbour->m_currentTileType == TileType::SAND)
		{
			hasSandNeighbour = true;
		}
	}

	if (hasWaterNeighbour) {
		m_possibleTiles = { TileType::SAND };
	}
	else if (hasSandNeighbour) {
		m_possibleTiles = { TileType::LAND };
	}
	else {
		m_possibleTiles = { TileType::LAND, TileType::SAND, TileType::WATER };
	}

	m_currentTileType = *m_possibleTiles.begin();

	determineColor();
}




