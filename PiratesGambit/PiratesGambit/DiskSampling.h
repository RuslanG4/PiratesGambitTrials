#pragma once
#include "Includes.h"
#include "Node.h"

class ObjectPlacement {
public:
    static ObjectPlacement& getInstance() {
        static ObjectPlacement instance;
        return instance;
    }

    static std::vector<std::shared_ptr<Node>> placeTrees(std::vector<std::shared_ptr<Node>>& availableNodes, int treeAmount) {
        ObjectPlacement& instance = getInstance();
        return instance.findValidAreas(availableNodes, treeAmount);
    }

    static std::shared_ptr<Node> placeBarrel(const std::vector<std::shared_ptr<Node>>& availableNodes) {
        ObjectPlacement& instance = getInstance();
        return instance.findBarrelArea(availableNodes);
    }

    ObjectPlacement(const ObjectPlacement&) = delete;
    ObjectPlacement& operator=(const ObjectPlacement&) = delete;

private:
    ObjectPlacement() = default;

    std::shared_ptr<Node> findBarrelArea(const std::vector<std::shared_ptr<Node>>& availableNodes)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        int randomIndex = rand() % availableNodes.size();
        std::shared_ptr<Node> startNode = availableNodes[randomIndex];

        while (!availableNodes.empty()) {
            for (auto& node : availableNodes) {
                node->updateTraversed(false);
            }

            std::vector<std::shared_ptr<Node>> area = PathFindingFunctions<Node>::BreathSearchEuclydianIslands(startNode, 2);

            if (area.size() >= 23 && !startNode->isOccupied() && !startNode->IsInBuildingArea() && startNode->getParentTileType() != SAND) {
                return startNode; 
            }

            randomIndex = rand() % availableNodes.size();
            startNode = availableNodes[randomIndex];
        }

        return nullptr; 
    }


    std::vector<std::shared_ptr<Node>> findValidAreas(std::vector<std::shared_ptr<Node>>& availableNodes, int treeAmount) {
        std::vector<std::shared_ptr<Node>> placedTrees;
        std::random_device rd;
        std::mt19937 gen(rd());

        while (!availableNodes.empty() && placedTrees.size() < treeAmount) {

            int randomIndex = rand() % availableNodes.size();

            std::shared_ptr<Node> startNode = availableNodes[randomIndex];

               while (startNode->getParentTileType() != LAND)
               {
                   availableNodes.erase(availableNodes.begin() + randomIndex);

                   randomIndex = rand() % availableNodes.size();
                   startNode = availableNodes[randomIndex];
               }
              if(availableNodes.empty())
              {
                  return placedTrees;
              }

                

            for(auto& node : availableNodes)
            {
                node->updateTraversed(false);
            }

            std::vector<std::shared_ptr<Node>> area = PathFindingFunctions<Node>::BreathSearchEuclydianIslands(startNode, 2);

            if (area.size() > 10 && isAreaValid(area)) {

                std::vector<std::shared_ptr<Node>> sampledNodes = samplePoints(area, treeAmount - placedTrees.size(), gen);

                placedTrees.insert(placedTrees.end(), sampledNodes.begin(), sampledNodes.end());

                for (const auto& node : sampledNodes) {
                    auto it = std::find(availableNodes.begin(), availableNodes.end(), node);
                    if (it != availableNodes.end()) {
                        availableNodes.erase(it);
                    }
                }
            }
            else {
                availableNodes.erase(availableNodes.begin() + randomIndex);
            }

        }
        return placedTrees;
    }

    bool isAreaValid(const std::vector<std::shared_ptr<Node>>& area) const {
        for (const auto& node : area) {
            if (node->isOccupied()) {
                return false;
            }
        }
        return true;
    }

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
