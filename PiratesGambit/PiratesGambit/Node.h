#pragma once
#include"Includes.h"
#include"TextureManager.h"

enum TileType
{
	WATER,
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

		waterBackSprite.setPosition(sf::Vector2f(gridX, gridY));
		waterBackSprite.setScale(size / 64.f, size / 64.f); //64x64 is size of texture

		debugShape.setPosition(sf::Vector2f(gridX, gridY));
		debugShape.setSize(sf::Vector2f(32, 32));
		debugShape.setFillColor(sf::Color(123,123,123,46));
	};

	void addNeighbour(Node* t_cellId);

	sf::Sprite drawableNode; //sfml render
	sf::Sprite waterBackSprite; //back texture of water

	sf::RectangleShape debugShape;
	bool drawDebug = false;

	std::unordered_set<TileType> m_possibleTiles{ TileType::LAND, TileType::GRASSY_LAND,TileType::WATER};

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
	void setWaterTexture(const sf::Texture& _texture) { waterBackSprite.setTexture(_texture); };

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

