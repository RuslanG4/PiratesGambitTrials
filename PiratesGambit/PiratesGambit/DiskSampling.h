#pragma once
#include"Includes.h"
#include "Node.h"

class PoissonDiskSampling {
public:
    static PoissonDiskSampling& getInstance() {
        static PoissonDiskSampling instance;
        return instance;
    }

    static std::vector<std::shared_ptr<Node>> generateObjects(const std::vector<std::shared_ptr<Node>>& availableNodes, int amount) {
        PoissonDiskSampling& instance = getInstance();
        int size = availableNodes[0]->getNodeData().size;
        instance.radius = (size * std::numbers::sqrt2);
        instance.availableNodes = availableNodes;
        return instance.generatePoints(amount);
    }

    PoissonDiskSampling(const PoissonDiskSampling&) = delete;
    PoissonDiskSampling& operator=(const PoissonDiskSampling&) = delete;
private:
    PoissonDiskSampling() = default;

    float radius;
    std::vector<std::shared_ptr<Node>> availableNodes;
    const int k = 100; // Number of attempts per point


    std::vector<std::shared_ptr<Node>> generatePoints(int amount) {
        std::vector<std::shared_ptr<Node>> nodes;
        std::queue<sf::Vector2f> processQueue;
        std::random_device rd;
        std::mt19937 gen(rd());

        std::shared_ptr<Node> firstNode = availableNodes[rand() % availableNodes.size()];

        while(!isNodeValid(firstNode))
        {
            firstNode = availableNodes[rand() % availableNodes.size()];
        }

        nodes.push_back(firstNode);
        processQueue.push(firstNode->getMidPoint());

        while (!processQueue.empty() && nodes.size() < amount) {
            sf::Vector2f point = processQueue.front();
            processQueue.pop();

            for (int i = 0; i < k && nodes.size() < amount; ++i) {

                sf::Vector2f newPoint = generateRandomPointAround(point, gen);
                auto newNode = IsPointValid(newPoint);

                if (isNodeValid(newNode)) {
                    newNode->updateOccupied(true);
                    nodes.push_back(newNode);
                    processQueue.push(newPoint);
                    break;
                }
            }
        }
        return nodes;
    }
    bool isNodeValid(const std::shared_ptr<Node>& _node) const
    {
        if (_node) {
            if (_node->getParentTileType() == LAND && !_node->IsInBuildingArea() && !_node->isOccupied())
            {
                return true;
            }
        }
        return false;
    }

    std::shared_ptr<Node> IsPointValid(const sf::Vector2f& _point)
    {
        // Loop through available nodes and check the conditions
        for (const auto& node : availableNodes) {
            if (Utility::collisionWithPoint(_point, node->getPosition(), sf::Vector2f(32, 32))) {
                // Return the node if it satisfies the conditions
                return node;
            }
        }

        // Return nullptr if no valid node was found
        return nullptr;
    }

    sf::Vector2f generateRandomPointAround(const sf::Vector2f& p, std::mt19937& gen) {
        std::uniform_real_distribution<float> distRadius(radius, 2 * radius);
        std::uniform_real_distribution<float> distAngle(0, 2 * Utility::PI); //0-360

        float r = distRadius(gen);

        float theta = distAngle(gen);

        sf::Vector2f newPoint = { p.x + r * std::cos(theta), p.y + r * std::sin(theta) };

        return newPoint;
    }
};
