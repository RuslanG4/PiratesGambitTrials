#pragma once
#include "BattleGridNode.h"
#include "Includes.h"
#include "Node.h"

/// <summary>
/// Comparison functor for priority queue sorting in A* pathfinding.
/// Compares two nodes based on their estimated total cost (F-cost),
/// using H-cost as a tiebreaker if the F-costs are equal.
/// </summary>
template <typename NodeType>
class Compare {
public:
    /// <summary>
    /// Overloaded operator to compare two nodes.
    /// </summary>
    /// <param name="a">First node.</param>
    /// <param name="b">Second node.</param>
    /// <returns>True if 'a' has a higher cost than 'b', false otherwise.</returns>
    bool operator()(const std::shared_ptr<NodeType>& a, const std::shared_ptr<NodeType>& b) {
        // Compare based on the total estimated cost (F-cost).
        if (a->getNodeData().fCost == b->getNodeData().fCost) {
            // Use H-cost as a tiebreaker (lower H-cost is preferred).
            return a->getNodeData().hCost > b->getNodeData().hCost;
        }
        return a->getNodeData().fCost > b->getNodeData().fCost;
    }
};

/// <summary>
/// A singleton class providing pathfinding algorithms such as A* and breadth-first search.
/// </summary>
template <typename NodeType>
class PathFindingFunctions
{
public:
    /// <summary>
    /// Retrieves the singleton instance of PathFindingFunctions.
    /// </summary>
    /// <returns>Reference to the singleton instance.</returns>
    static PathFindingFunctions& getInstance()
    {
        static PathFindingFunctions instance;
        return instance;
    }

    /// <summary>
    /// Performs A* pathfinding to find the shortest path between two nodes.
    /// </summary>
    /// <param name="_area">The search area containing all nodes.</param>
    /// <param name="_start">Starting node.</param>
    /// <param name="end">Destination node.</param>
    /// <returns>A vector of shared pointers representing the shortest path.</returns>
    static std::vector<std::shared_ptr<NodeType>> aStarPathFind(
        const std::vector<std::shared_ptr<NodeType>>& _area,
        const std::shared_ptr<NodeType>& _start,
        const std::shared_ptr<NodeType>& end
    );

    /// <summary>
    /// Performs a breadth-first search to find all nodes within a given depth.
    /// </summary>
    /// <param name="_area">The search area.</param>
    /// <param name="_startNode">Starting node.</param>
    /// <param name="_depth">Search depth.</param>
    /// <returns>A vector of node indices that are within the given depth.</returns>
    static std::vector<int> BreathSearchNodes(
        const std::vector<std::shared_ptr<NodeType>>& _area,
        const std::shared_ptr<NodeType>& _startNode,
        int _depth
    );

    /// <summary>
    /// Performs a breadth-first search using Euclidean distance as a constraint.
    /// </summary>
    /// <param name="_area">The search area.</param>
    /// <param name="_startNode">Starting node.</param>
    /// <param name="_depth">Search depth.</param>
    /// <returns>A vector of node indices found within the Euclidean range.</returns>
    static std::vector<int> BreathSearchEuclydianNodes(
        const std::vector<std::shared_ptr<NodeType>>& _area,
        const std::shared_ptr<NodeType>& _startNode,
        int _depth
    );

    /// <summary>
    /// Performs a breadth-first search to find connected island nodes using Euclidean distance.
    /// </summary>
    /// <param name="_startNode">Starting node.</param>
    /// <param name="_depth">Search depth.</param>
    /// <returns>A vector of shared pointers to the discovered island nodes.</returns>
    static std::vector<std::shared_ptr<NodeType>> BreathSearchEuclydianIslands(
        const std::shared_ptr<NodeType>& _startNode,
        int _depth
    );

private:
    /// <summary>
    /// Private constructor to enforce the singleton pattern.
    /// </summary>
    PathFindingFunctions() = default;
};

// Include the implementation file for function definitions.
#include "PathFinding.inl"
