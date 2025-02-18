#pragma once
#include "BaseNode.h"
#include"Includes.h"
#include"TextureManager.h"

/// <summary>
/// Handles individual grid nodes inside tile-map
/// </summary>
class Node : public BaseNode
{
public:
	//copy
	Node(const Node& other, bool island) :
		BaseNode(other.nodeData), isLand(island)
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

	Node(const NodeData& _data) :
		BaseNode(_data)
	{
		drawableNode = std::make_shared<sf::Sprite>();
		waterBackSprite = std::make_shared<sf::Sprite>();
		debugShape = std::make_shared<sf::RectangleShape>();

		drawableNode->setPosition(sf::Vector2f(nodeData.gridX, nodeData.gridY));
		drawableNode->setScale(nodeData.size / 64.f, nodeData.size / 64.f); //64x64 is size of texture

		waterBackSprite->setPosition(sf::Vector2f(nodeData.gridX, nodeData.gridY));
		waterBackSprite->setScale(nodeData.size / 64.f, nodeData.size / 64.f); //64x64 is size of texture

		debugShape->setPosition(sf::Vector2f(nodeData.gridX, nodeData.gridY));
		debugShape->setSize(sf::Vector2f(nodeData.size, nodeData.size));
		debugShape->setFillColor(sf::Color(123,123,123,46));
	}

	void addNeighbour(const std::shared_ptr<BaseNode>& t_cellId, int _neighbourPos) override;

	const std::vector<std::pair<std::shared_ptr<Node>, int>>& getNeighbours();

	std::shared_ptr<sf::Sprite> drawableNode; //sfml render
	std::shared_ptr<sf::Sprite> waterBackSprite; //back texture of water
	std::shared_ptr<sf::RectangleShape> debugShape;

	//Getters
	int getChunkId() const { return m_chunkId; }
	bool getIsLand() const { return isLand; }

	//Tiles
	TileType getTileType() const { return m_currentTileType; };
	ParentTileType getParentTileType() const { return m_currentParentTileType; }

	//Setters
	void setChunkID(int _id) { m_chunkId = _id; }
	void setLand(bool _land) { isLand = _land; }

	void UpdateIsBuildingArea(bool _bool) { isBuildingArea = _bool; }
	bool IsInBuildingArea() const { return isBuildingArea; }

	void setTileType(TileType _type) { m_currentTileType = _type; }
	void setParentTileType(ParentTileType _type) { m_currentParentTileType = _type; }
	void setWaterTexture(const sf::Texture& _texture) const { waterBackSprite->setTexture(_texture); }

private:
	std::vector<std::pair<std::shared_ptr<Node>, int>> m_neighbours;

	std::vector<std::pair<std::shared_ptr<Node>, int>> subDividedNodes;

	int m_chunkId;
	bool isLand{ false };
	bool isBuildingArea{ false };

	TileType m_currentTileType;
	ParentTileType m_currentParentTileType;
};

