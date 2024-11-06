#pragma once
#include"Includes.h"
#include"TextureManager.h"

class Node
{
public:
	//copy constructor
	Node(const Node& other) :
		gridX(other.gridX),
		gridY(other.gridY),
		isLand(other.isLand),
		size(other.size),
		m_neighbours(other.getNeighbours())
	{
		if (other.drawableNode) {
			drawableNode = std::make_shared<sf::Sprite>(*other.drawableNode);
		}
		if (other.waterBackSprite) {
			waterBackSprite = std::make_shared<sf::Sprite>(*other.waterBackSprite);
		}
		if (other.debugShape) {
			debugShape = std::make_shared<sf::RectangleShape>(*other.debugShape);
		}
	}
	//
	Node(int _gridX, int _gridY, int size_, bool _isLand) :
		gridX(_gridX),
		gridY(_gridY),
		isLand(_isLand),
		size(size_)
	{
		drawableNode = std::make_shared<sf::Sprite>();
		waterBackSprite = std::make_shared<sf::Sprite>();
		debugShape = std::make_shared<sf::RectangleShape>();

		drawableNode->setPosition(sf::Vector2f(gridX, gridY));
		drawableNode->setScale(size / 64.f, size / 64.f); //64x64 is size of texture

		waterBackSprite->setPosition(sf::Vector2f(gridX, gridY));
		waterBackSprite->setScale(size / 64.f, size / 64.f); //64x64 is size of texture

		debugShape->setPosition(sf::Vector2f(gridX, gridY));
		debugShape->setSize(sf::Vector2f(size, size));
		debugShape->setFillColor(sf::Color(123,123,123,46));
	};

	void addNeighbour(Node* t_cellId);

	std::shared_ptr<sf::Sprite> drawableNode; //sfml render
	std::shared_ptr<sf::Sprite> waterBackSprite; //back texture of water
	std::shared_ptr<sf::RectangleShape> debugShape;

	//Getters
	int getChunkId() const { return m_chunkId; };
	int getID() const { return m_id; };
	std::vector<Node*> getNeighbours() const { return m_neighbours; };
	bool getMarked() const{ return visited; };
	bool getIsLand() const { return isLand; };
	int getSize() const { return size; };
	sf::Vector2f getPosition() const { return { static_cast<float>(gridX), static_cast<float>(gridY)}; }

	//Tiles
	TileType getTileType() const { return m_currentTileType; };
	ParentTileType getParentTileType() const { return m_currentParentTileType; };

	//Setters
	void setID(int _id) { m_id = _id; };
	void setChunkID(int _id) { m_chunkId = _id; };
	void setMarked() { visited = !visited; };
	void setLand(bool _land) { isLand = _land; };
	void setTileType(TileType _type) { m_currentTileType = _type; };
	void setParentTileType(ParentTileType _type) { m_currentParentTileType = _type; };
	void setWaterTexture(const sf::Texture& _texture) const { waterBackSprite->setTexture(_texture); };

	//Resetters
	void resetMarked() { visited = false; };

private:
	int m_id;
	int m_chunkId;

	int size;
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

