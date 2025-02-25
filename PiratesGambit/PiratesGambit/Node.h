#pragma once
#include "BaseNode.h"
#include "Includes.h"
#include "TextureManager.h"

/// <summary>
/// Represents an individual grid node inside a tile-based map.
/// Inherits from BaseNode and handles graphical representation, neighbors, and tile properties.
/// </summary>
class Node : public BaseNode
{
public:
    /// <summary>
    /// Copy constructor to create a new node based on another node.
    /// Copies all graphical elements if they exist.
    /// </summary>
    /// <param name="other">Node to copy from.</param>
    /// <param name="island">Indicates whether the node belongs to an island.</param>
    Node(const Node& other, bool island) :
        BaseNode(other.nodeData)
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

    /// <summary>
    /// Constructor that initializes a node with position, scaling, and debug shape.
    /// </summary>
    /// <param name="_data">Node data containing position, size, and other properties.</param>
    Node(const NodeData& _data) :
        BaseNode(_data)
    {
        drawableNode = std::make_shared<sf::Sprite>();
        waterBackSprite = std::make_shared<sf::Sprite>();
        debugShape = std::make_shared<sf::RectangleShape>();

        // Set position and scale based on grid coordinates and tile size.
        drawableNode->setPosition(sf::Vector2f(nodeData.gridX, nodeData.gridY));
        drawableNode->setScale(nodeData.size / 64.f, nodeData.size / 64.f); // 64x64 is the texture size.

        waterBackSprite->setPosition(sf::Vector2f(nodeData.gridX, nodeData.gridY));
        waterBackSprite->setScale(nodeData.size / 64.f, nodeData.size / 64.f);

        debugShape->setPosition(sf::Vector2f(nodeData.gridX, nodeData.gridY));
        debugShape->setSize(sf::Vector2f(nodeData.size, nodeData.size));
        debugShape->setFillColor(sf::Color(123, 123, 123, 46)); // Semi-transparent debug color.
    }

    /// <summary>
    /// Adds a neighbor to the node at a specific position.
    /// </summary>
    /// <param name="t_cellId">The neighboring node.</param>
    /// <param name="_neighbourPos">The position of the neighbor relative to this node.</param>
    void addNeighbour(const std::shared_ptr<BaseNode>& t_cellId, int _neighbourPos) override;

    /// <summary>
    /// Retrieves a list of neighboring nodes with their relative positions.
    /// </summary>
    /// <returns>Vector of neighbor node references paired with their position indices.</returns>
    const std::vector<std::pair<std::shared_ptr<Node>, int>>& getNeighbours();

    // Graphical elements
    std::shared_ptr<sf::Sprite> drawableNode; ///< Rendered node sprite.
    std::shared_ptr<sf::Sprite> waterBackSprite; ///< Background water texture.
    std::shared_ptr<sf::RectangleShape> debugShape; ///< Debug visualization of the node.

    /// <summary>
    /// Retrieves the ID of the chunk this node belongs to.
    /// </summary>
    /// <returns>Chunk ID.</returns>
    int getChunkId() const { return m_chunkId; }

    /// <summary>
    /// Retrieves the tile type of this node.
    /// </summary>
    /// <returns>The current tile type.</returns>
    TileType getTileType() const { return m_currentTileType; }

    /// <summary>
    /// Retrieves the parent tile type of this node.
    /// </summary>
    /// <returns>The current parent tile type.</returns>
    ParentTileType getParentTileType() const { return m_currentParentTileType; }

    /// <summary>
    /// Sets the chunk ID of the node.
    /// </summary>
    /// <param name="_id">New chunk ID.</param>
    void setChunkID(int _id) { m_chunkId = _id; }

    /// <summary>
    /// Marks the node as a buildable area or not.
    /// </summary>
    /// <param name="_bool">True if the node is in a buildable area, false otherwise.</param>
    void UpdateIsBuildingArea(bool _bool) { isBuildingArea = _bool; }

    /// <summary>
    /// Checks whether the node is within a buildable area.
    /// </summary>
    /// <returns>True if the node is in a buildable area.</returns>
    bool IsInBuildingArea() const { return isBuildingArea; }

    /// <summary>
    /// Sets the tile type of the node.
    /// </summary>
    /// <param name="_type">New tile type.</param>
    void setTileType(TileType _type) { m_currentTileType = _type; }

    /// <summary>
    /// Sets the parent tile type of the node.
    /// </summary>
    /// <param name="_type">New parent tile type.</param>
    void setParentTileType(ParentTileType _type) { m_currentParentTileType = _type; }

    /// <summary>
    /// Sets the texture of the water background sprite.
    /// </summary>
    /// <param name="_texture">SFML texture reference.</param>
    void setWaterTexture(const sf::Texture& _texture) const { waterBackSprite->setTexture(_texture); }

private:
    std::vector<std::pair<std::shared_ptr<Node>, int>> m_neighbours; ///< List of neighboring nodes and their positions.
    std::vector<std::pair<std::shared_ptr<Node>, int>> subDividedNodes; ///< Subdivided nodes for complex structures.

    int m_chunkId; ///< ID of the chunk this node belongs to.

    bool isBuildingArea{ false }; ///< Indicates whether this node is in a buildable area.

    TileType m_currentTileType; ///< Current tile type of the node.
    ParentTileType m_currentParentTileType; ///< Parent tile type for hierarchical tile representation.
};
