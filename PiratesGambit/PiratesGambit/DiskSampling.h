#pragma once
#include "Includes.h"
#include "Node.h"

/// <summary>
/// Places Objects like barrels and trees depending on a surrounding area
/// </summary>
class ObjectPlacement {
public:
    static ObjectPlacement& getInstance() {
        static ObjectPlacement instance;
        return instance;
    }
    /// <summary>
    /// Finds area to place trees
    /// </summary>
    /// <param name="availableNodes">Area to search</param>
    /// <param name="treeAmount">Amount of desired trees in clump</param>
    /// <returns>Nodes where trees should be placed</returns>
    static std::vector<std::shared_ptr<Node>> placeTrees(std::vector<std::shared_ptr<Node>>& availableNodes, int treeAmount) {
        ObjectPlacement& instance = getInstance();
        return instance.findValidAreas(availableNodes, treeAmount);
    }
    /// <summary>
    /// Finds where to place barrels
    /// </summary>
    /// <param name="availableNodes">Area to search</param>
    /// <returns>Node where to place barrel</returns>
    static std::shared_ptr<Node> placeBarrel(std::vector<std::shared_ptr<Node>>& availableNodes) {
        ObjectPlacement& instance = getInstance();
        return instance.findBarrelArea(availableNodes);
    }

    ObjectPlacement(const ObjectPlacement&) = delete;
    ObjectPlacement& operator=(const ObjectPlacement&) = delete;

private:
    ObjectPlacement() = default;

    /// <summary>
    /// Searches through area to find at least a 3x3 open area so a barrel can be placed
    /// </summary>
    /// <param name="availableNodes">Search area</param>
    /// <returns>Node where barrel should be placed</returns>
    std::shared_ptr<Node> findBarrelArea(std::vector<std::shared_ptr<Node>>& availableNodes)
    {
        while (!availableNodes.empty()) {
            int randomIndex = std::rand() % availableNodes.size();
            std::shared_ptr<Node> startNode = availableNodes[randomIndex]; // random start node

            std::vector<std::shared_ptr<Node>> area = PathFindingFunctions<Node>::BreathSearchEuclydianIslands(startNode, 2);

            if (area.size() >= 9 && isAreaValid(area)) {
                for (auto& node : area) {
                    //node->debugShape->setFillColor(sf::Color::Yellow); //debug
                    node->UpdateIsBuildingArea(true); //mark area as in use
                }
                return startNode; //return node
            }

            availableNodes.erase(availableNodes.begin() + randomIndex); //remove node from search area (invalid)
        }

        return nullptr;
    }

    /// <summary>
    /// Finds a valid area to place a clump of trees and selects random nodes in that area 
    /// </summary>
    /// <param name="availableNodes">Search nodes</param>
    /// <param name="treeAmount">Amount of trees</param>
    /// <returns>Nodes where to place trees</returns>
    std::vector<std::shared_ptr<Node>> findValidAreas(std::vector<std::shared_ptr<Node>>& availableNodes, int treeAmount) {
        std::vector<std::shared_ptr<Node>> placedTrees;
        std::random_device rd;
        std::mt19937 gen(rd());

        while (!availableNodes.empty() && placedTrees.size() < treeAmount) {
            int randomIndex = std::rand() % availableNodes.size(); 
            std::shared_ptr<Node> startNode = availableNodes[randomIndex]; //random node

            //make sure it's on grass
            while (startNode->getParentTileType() != LAND) {
                availableNodes.erase(availableNodes.begin() + randomIndex);
                if (availableNodes.empty()) {
                    return placedTrees;
                }
                randomIndex = std::rand() % availableNodes.size();
                startNode = availableNodes[randomIndex];
            }

            std::vector<std::shared_ptr<Node>> area = PathFindingFunctions<Node>::BreathSearchEuclydianIslands(startNode, 3);

            //Is the depth area large enough, excludes areas too close to an edge
            if (area.size() >= 15 && isAreaValid(area)) {
                for (auto& node : area) {
                    node->UpdateIsBuildingArea(true); //set are as in use for future clumps
                }

                std::vector<std::shared_ptr<Node>> sampledNodes = samplePoints(area, treeAmount, gen); //randomly pick nodes
                placedTrees.insert(placedTrees.end(), sampledNodes.begin(), sampledNodes.end());

                //remove nodes from search area in future
                availableNodes.erase(
                    std::ranges::remove_if(availableNodes, [&sampledNodes](const std::shared_ptr<Node>& node) {
                        return std::ranges::find(sampledNodes, node) != sampledNodes.end();
                        }).begin(), availableNodes.end()
                        );
            }
            else {
                availableNodes.erase(availableNodes.begin() + randomIndex);
            }
        }

        return placedTrees; //return nodes
    }

    /// <summary>
    /// See if area of nodes is valid to place an object
    /// </summary>
    /// <param name="area">Search space</param>
    /// <returns>True/False</returns>
    bool isAreaValid(const std::vector<std::shared_ptr<Node>>& area) const {
        for (const auto& node : area) {
            if (node->isOccupied() || node->IsInBuildingArea()) {
                return false;
            }
        }
        return true;
    }

    /// <summary>
    /// Generate random points in an area to place trees
    /// </summary>
    /// <param name="area">Search space</param>
    /// <param name="maxSamples">how many trees</param>
    /// <param name="gen">random generate</param>
    /// <returns>Vector of nodes to put trees</returns>
    std::vector<std::shared_ptr<Node>> samplePoints(std::vector<std::shared_ptr<Node>>& area, int maxSamples, std::mt19937& gen) {
        std::vector<std::shared_ptr<Node>> sampledNodes;
        std::ranges::shuffle(area.begin(), area.end(), gen);

        for (auto& node : area) {
            if (sampledNodes.size() >= maxSamples) break;
            node->updateOccupied(true);
            sampledNodes.push_back(node);
        }

        return sampledNodes;
    }
};
