#pragma once
#include "BaseNode.h"
#include"Includes.h"
#include "Structs.h"

class BattleGridNode : public BaseNode
{
public:
	BattleGridNode(const NodeData& _data) :
		 BaseNode(_data)
	{
		debugShape = std::make_unique<sf::RectangleShape>();
		walkableArea = std::make_unique<sf::RectangleShape>();

		debugShape->setPosition(sf::Vector2f(nodeData.gridX, nodeData.gridY));
		debugShape->setSize(sf::Vector2f(nodeData.size, nodeData.size));
		debugShape->setFillColor(sf::Color(123, 123, 123, 46));
		debugShape->setOutlineThickness(2);
		debugShape->setOutlineColor(sf::Color::White);


		walkableArea->setPosition(sf::Vector2f(nodeData.gridX, nodeData.gridY));
		walkableArea->setSize(sf::Vector2f(nodeData.size, nodeData.size));
		walkableArea->setFillColor(sf::Color(123, 123, 123, 46));
	};

	void addNeighbour(const std::shared_ptr<BaseNode>& t_cellId, int _neighbourPos) override;
	void setPrevious(const std::shared_ptr<BaseNode>& _previous) override;

	const std::vector<std::pair<std::shared_ptr<BattleGridNode>, int>>& getNeighbours();
	const std::shared_ptr<BattleGridNode>& getPrevious();

	std::unique_ptr<sf::RectangleShape> debugShape;
	std::unique_ptr<sf::RectangleShape> walkableArea;

private:
	std::shared_ptr<BattleGridNode> previousNode;
	std::vector<std::pair<std::shared_ptr<BattleGridNode>, int>> m_neighbours;
};

