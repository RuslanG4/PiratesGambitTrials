#pragma once
#include "Includes.h"
#include "Structs.h"

/// <summary>
/// Represents a base class for a node in a grid-based system.
/// Nodes store positional data, traversal information, and relationships with neighbors.
/// </summary>
class BaseNode
{
public:
    /// <summary>
    /// Constructs a BaseNode with the given node data.
    /// </summary>
    /// <param name="_data">The data containing the node's properties.</param>
    BaseNode(const NodeData& _data) : nodeData(_data) {}

    /// <summary>
    /// Adds a neighbor node at a specific position.
    /// Must be implemented in derived classes.
    /// </summary>
    /// <param name="t_cellId">Shared pointer to the neighboring node.</param>
    /// <param name="_neighbourPos">Position of the neighbor in relation to this node.</param>
    virtual void addNeighbour(const std::shared_ptr<BaseNode>& t_cellId, int _neighbourPos) = 0;

    /// <summary>
    /// Sets the previous node in a traversal path.
    /// </summary>
    /// <param name="_previous">Shared pointer to the previous node.</param>
    virtual void setPrevious(const std::shared_ptr<BaseNode>& _previous) { previousNode = _previous; }

    /// <summary>
    /// Clears the reference to the previous node.
    /// </summary>
    void clearPrevious() { previousNode = nullptr; }

    // Getters

    /// <summary>
    /// Gets the unique ID of the node.
    /// </summary>
    /// <returns>Node ID.</returns>
    int getID() const { return nodeData.m_id; }

    /// <summary>
    /// Checks if the node is occupied.
    /// </summary>
    /// <returns>True if occupied, false otherwise.</returns>
    bool isOccupied() const { return nodeData.occupied; }

    /// <summary>
    /// Checks if the node has been traversed.
    /// </summary>
    /// <returns>True if traversed, false otherwise.</returns>
    bool hasBeenTraversed() const { return nodeData.traversed; }

    /// <summary>
    /// Gets the movement vector associated with the node.
    /// </summary>
    /// <returns>Movement vector as sf::Vector2f.</returns>
    sf::Vector2f getMovementVector() const { return movementVector; }

    /// <summary>
    /// Gets a reference to the node's data.
    /// </summary>
    /// <returns>Reference to the NodeData struct.</returns>
    NodeData& getNodeData() { return nodeData; }

    /// <summary>
    /// Gets the previous node in a traversal path.
    /// </summary>
    /// <returns>Shared pointer to the previous node.</returns>
    const std::shared_ptr<BaseNode>& getPrevious() { return previousNode; }

    /// <summary>
    /// Checks if the node represents land.
    /// </summary>
    /// <returns>True if it is land, false otherwise.</returns>
    bool getIsLand() const { return nodeData.isLand; }

    /// <summary>
    /// Sets whether the node represents land.
    /// </summary>
    /// <param name="_land">True if the node is land, false otherwise.</param>
    void setLand(bool _land) { nodeData.isLand = _land; }

    /// <summary>
    /// Gets the position of the node in grid coordinates.
    /// </summary>
    /// <returns>Position as sf::Vector2f.</returns>
    sf::Vector2f getPosition() const { return { static_cast<float>(nodeData.gridX), static_cast<float>(nodeData.gridY) }; }

    /// <summary>
    /// Gets the midpoint of the node, useful for positioning entities at the center.
    /// </summary>
    /// <returns>Midpoint as sf::Vector2f.</returns>
    sf::Vector2f getMidPoint() const { return { static_cast<float>(nodeData.gridX + (nodeData.size / 2)), static_cast<float>(nodeData.gridY + (nodeData.size / 2)) }; }

    // Setters

    /// <summary>
    /// Sets the unique ID of the node.
    /// </summary>
    /// <param name="_id">New ID for the node.</param>
    void setID(int _id) { nodeData.m_id = _id; }

    /// <summary>
    /// Updates the occupied status of the node.
    /// </summary>
    /// <param name="_status">True if occupied, false otherwise.</param>
    void updateOccupied(bool _status) { nodeData.occupied = _status; }

    /// <summary>
    /// Updates the traversed status of the node.
    /// </summary>
    /// <param name="_status">True if the node has been traversed, false otherwise.</param>
    void updateTraversed(bool _status) { nodeData.traversed = _status; }

    /// <summary>
    /// Sets the movement vector for the node.
    /// </summary>
    /// <param name="_vec">New movement vector.</param>
    void setMovementVector(sf::Vector2f _vec) { movementVector = _vec; }

    /// <summary>
    /// Sets the F-cost (total estimated cost) for pathfinding.
    /// </summary>
    /// <param name="_cost">New F-cost.</param>
    void setFCost(float _cost) { nodeData.fCost = _cost; }

    /// <summary>
    /// Sets the G-cost (movement cost from the start node).
    /// </summary>
    /// <param name="_cost">New G-cost.</param>
    void setGCost(float _cost) { nodeData.gCost = _cost; }

    /// <summary>
    /// Sets the H-cost (heuristic cost to the destination).
    /// </summary>
    /// <param name="_cost">New H-cost.</param>
    void setHCost(float _cost) { nodeData.hCost = _cost; }

    // Resetters

    /// <summary>
    /// Resets the occupied status of the node.
    /// </summary>
    void resetMarked() { nodeData.occupied = false; }

protected:
    /// <summary>
    /// Protected destructor to prevent direct deletion of BaseNode instances.
    /// </summary>
    ~BaseNode() = default;

    NodeData nodeData;  // Data structure holding node attributes
    std::shared_ptr<BaseNode> previousNode;  // Pointer to the previous node in traversal
    sf::Vector2f movementVector{ 0,0 };  // Directional movement vector

private:
    // Currently, no private members are defined.
};
