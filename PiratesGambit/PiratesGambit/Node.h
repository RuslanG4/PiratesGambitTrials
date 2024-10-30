#pragma once
#include"Includes.h"
#include"TextureManager.h"

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

	//Getters
	int getID() const { return m_id; };
	std::vector<Node*> getNeighbours() const { return m_neighbours; };
	bool getMarked() const{ return visited; };
	bool getIsLand() const { return isLand; };

	//Tiles
	TileType getTileType() const { return m_currentTileType; };
	ParentTileType getParentTileType() const { return m_currentParentTileType; };

	//Setters
	void setID(int _id) { m_id = _id; };
	void setMarked() { visited = !visited; };
	void setLand(bool _land) { isLand = _land; };
	void setTileType(TileType _type) { m_currentTileType = _type; };
	void setParentTileType(ParentTileType _type) { m_currentParentTileType = _type; };
	void setWaterTexture(const sf::Texture& _texture) { waterBackSprite.setTexture(_texture); };

	//Resetters
	void resetMarked() { visited = false; };

	int height = std::rand() % 8 + 1;

private:
	int m_id;
	bool visited{ false };
	bool isLand{ false };

	std::vector<Node*> m_neighbours;  
	//							  0 3 5	
	// structure of neighbours -> 1 X 6
	//							  2 4 7
	TileType m_currentTileType;
	ParentTileType m_currentParentTileType;

	int gridX; //position x
	int gridY; //position y
};

