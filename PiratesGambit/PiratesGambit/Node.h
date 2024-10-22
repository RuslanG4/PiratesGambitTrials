#pragma once
#include"Includes.h"

enum TileType
{
	WATER,
	EDGE_SAND,
	SAND,
	LAND,
};

class Node
{
public:
	Node(int _gridX, int _gridY, int size, sf::Font& _font, bool _isWall) :
		gridX(_gridX),
		gridY(_gridY),
		font(_font),
		isWall(_isWall)
	{
		nodeCostText.setFont(font);
		nodeCostText.setFillColor(sf::Color::Black);
		/*nodeCostText.setString(std::to_string(nodeRules.size()));*/
		nodeCostText.setCharacterSize(12);

		drawableNode.setSize(sf::Vector2f(size, size));
		drawableNode.setPosition(sf::Vector2f(gridX, gridY));
		drawableNode.setOutlineColor(sf::Color::Black);
		drawableNode.setOutlineThickness(2.f);

		nodeCostText.setPosition(sf::Vector2f(gridX, gridY));

		//m_possibleTiles = { WATER, SAND, LAND};
		//determineEntropy();

		noiseColor();
	};

	void addNeighbour(Node* t_cellId) { m_neighbours.push_back(t_cellId); }
	std::vector<Node*> getNeighbours() { return m_neighbours; };

	void setID(int _id) { m_id = _id; };
	int getID() { return m_id; };

	void setMarked() { visited = !visited; };
	bool getMarked() { return visited; };
	void resetMarked() { visited = false; };

	void determineColor();
	void noiseColor();

	sf::RectangleShape drawableNode; //sfml render
	sf::Text nodeCostText;

	std::unordered_set<TileType> m_possibleTiles{ TileType::LAND, TileType::WATER, TileType::SAND };;

	void determineTile();

	bool isWall{ false };

	TileType m_currentTileType;

private:
	int m_id;
	bool visited{ false };

	std::vector<Node*> m_neighbours;

	int gridX; //position x
	int gridY; //position y

	sf::Font& font;

};

