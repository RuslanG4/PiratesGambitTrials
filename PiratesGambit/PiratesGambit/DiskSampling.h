#pragma once
#include"Includes.h"
#include "Node.h"

class PoissonDiskSampling {
public:
    static PoissonDiskSampling& getInstance() {
        static PoissonDiskSampling instance;
        return instance;
    }

    static std::vector<sf::Vector2f> generate(const std::vector<std::shared_ptr<Node>>& availableNodes) {
        PoissonDiskSampling& instance = getInstance();
        int size = availableNodes[0]->getNodeData().size;
        instance.radius = (size * std::numbers::sqrt2) / 2.f;
        instance.availableNodes = availableNodes;
        return instance.generatePoints();
    }

    PoissonDiskSampling(const PoissonDiskSampling&) = delete;
    PoissonDiskSampling& operator=(const PoissonDiskSampling&) = delete;
private:
    PoissonDiskSampling() = default;

    float radius;
    std::vector<std::shared_ptr<Node>> availableNodes;
    const int k = 30; // Number of attempts per point

    std::vector<sf::Vector2f> generatePoints() {
        std::vector<sf::Vector2f> points;
        std::queue<sf::Vector2f> processQueue;
        std::random_device rd;
        std::mt19937 gen(rd());

        sf::Vector2f firstPoint = availableNodes[rand() % availableNodes.size()]->getMidPoint();

        points.push_back(firstPoint);
        processQueue.push(firstPoint);

        while (!processQueue.empty() && points.size() < 30) {
            sf::Vector2f point = processQueue.front();
            processQueue.pop();

            for (int i = 0; i < k && points.size() < 30; ++i) {

                sf::Vector2f newPoint = generateRandomPointAround(point, gen);


                if (isValid(newPoint, points) && IsPointValid(newPoint)) {
                    points.push_back(newPoint);
                    processQueue.push(newPoint);
                    break;
                }
            }
        }
        return points;
    }

    bool isValid(const sf::Vector2f& p, const std::vector<sf::Vector2f>& points) {
        return !std::ranges::any_of(points, [&](const sf::Vector2f& existing) {
            float distSq = (p.x - existing.x) * (p.x - existing.x) + (p.y - existing.y) * (p.y - existing.y);
            return distSq < radius * radius;
            });
    }

    bool IsPointValid(const sf::Vector2f& _point)
    {
        return std::ranges::any_of(availableNodes, [&_point](const auto& node) {
            return Utility::collisionWithPoint(_point, node->getPosition(), sf::Vector2f(32, 32)) &&
                node->getParentTileType() == LAND; 
            });
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
