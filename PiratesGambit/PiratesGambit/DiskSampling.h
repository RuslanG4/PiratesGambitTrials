#pragma once

#include"Includes.h"
#include "Node.h"

class DiskSampling
{
public:
    static std::vector<std::shared_ptr<Node>> BreathFindNodes(const std::vector<std::shared_ptr<Node>>& _island, const std::shared_ptr<Node>& _startNode, int _depth)
    {
        std::queue<std::pair<std::shared_ptr<Node>, int>> nodeQueue;
        std::vector<std::shared_ptr<Node>> BreathArea;

        sf::Vector2f startPos = _startNode->getPosition();
        nodeQueue.emplace(_startNode, 0);
        _startNode->updateTraversed(true);

        bool collecting = false; // Flag to start collecting nodes at the required depth

        while (!nodeQueue.empty())
        {
            auto [currentNode, currentDistance] = nodeQueue.front();
            nodeQueue.pop();

            if (currentDistance == _depth)
            {
                collecting = true; // Start collecting nodes at this depth
                BreathArea.push_back(currentNode);
                continue;
            }

            if (collecting) break; // Exit the loop once all nodes at _depth have been collected

            auto neighbours = currentNode->getNeighbours();
            for (auto& neighbour : neighbours)
            {
                if (!neighbour.first->hasBeenTraversed() && neighbour.second % 2 != 0)
                {
                    neighbour.first->updateTraversed(true);

                    float dx = static_cast<float>(neighbour.first->getPosition().x - startPos.x);
                    float dy = static_cast<float>(neighbour.first->getPosition().y - startPos.y);

                    float distance = std::hypotf(dx / neighbour.first->getNodeData().size, dy / neighbour.first->getNodeData().size);

                    int roundedDistance = static_cast<int>(std::ceil(distance));

                    nodeQueue.emplace(neighbour.first, roundedDistance);

                    if (roundedDistance == _depth)
                    {
                        BreathArea.push_back(neighbour.first);
                    }
                }
            }
        }

        return BreathArea;
    }


private:
};
