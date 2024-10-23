#pragma once
#include"Includes.h"
#include"TextureManager.h"

enum TileType
{
	WATER,
	SAND,
	LAND,
	GRASSY_LAND
};

class Node
{
public:
	Node(int _gridX, int _gridY, int size, bool _isLand) :
		gridX(_gridX),
		gridY(_gridY),
		isLand(_isLand)
	{
		drawableNode.setPosition(sf::Vector2f(gridX, gridY));
		drawableNode.setScale(size / 64.f, size / 64.f); //64x64 is size of texture
	};

	void addNeighbour(Node* t_cellId);

	sf::Sprite drawableNode; //sfml render
	std::unordered_set<TileType> m_possibleTiles{ TileType::LAND, TileType::WATER, TileType::SAND };

	//Getters
	int getID() const { return m_id; };
	std::vector<Node*> getNeighbours() const { return m_neighbours; };
	bool getMarked() const{ return visited; };
	bool getIsLand() const { return isLand; };
	TileType getTileType() const { return m_currentTileType; };

	//Setters
	void setID(int _id) { m_id = _id; };
	void setMarked() { visited = !visited; };
	void setLand(bool _land) { isLand = _land; };
	void setTileType(TileType _type) { m_currentTileType = _type; };
	void setTexture(const sf::Texture& _texture) { drawableNode.setTexture(_texture); };

	//Resetters
	void resetMarked() { visited = false; };

private:
	int m_id;
	bool visited{ false };
	bool isLand{ false };

	std::vector<Node*> m_neighbours;  
	//							  0 3 5	
	// structure of neighbours -> 1 X 6
	//							  2 4 7
	TileType m_currentTileType;

	int gridX; //position x
	int gridY; //position y
};

