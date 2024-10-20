#pragma once
#include"Includes.h"

enum NodeType
{
	WATER,
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

		determineColor();
	};

	void addNeighbour(Node* t_cellId) { m_neighbours.push_back(t_cellId); }
	std::vector<Node*> getNeighbours() { return m_neighbours; };

	void setID(int _id) { m_id = _id; };
	int getID() { return m_id; };

	void setMarked() { visited = !visited; };
	bool getMarked() { return visited; };

	void updatePath(sf::Color _col);

	void setType(NodeType _type);
	void determineColor();

	sf::RectangleShape drawableNode; //sfml render
	sf::Text nodeCostText;

	std::unordered_set<NodeType> m_possibleTiles;
	int entropy;

	void updateNodeTypes(std::vector<NodeType> _surroundingTypes);

	void determineEntropy();
	void determineTile();


	bool drawn{ false };

	int height = std::rand() % 8 + 1;

	bool isWall{ false };

private:
	int m_id;
	bool visited{ false };

	std::vector<Node*> m_neighbours;

	std::map<NodeType, double> tileWeights = {
{ WATER, 0.6 }, // For example, water has a low chance
{ SAND, 1.0 },  // Base weight for sand
{ LAND, 2.00 }   // 60% more chance to get land
	};

	int gridX; //position x
	int gridY; //position y

	sf::Font& font;

};

