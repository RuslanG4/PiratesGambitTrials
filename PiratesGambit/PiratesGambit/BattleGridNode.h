#pragma once
#include "BaseNode.h"

class BattleGridNode : public BaseNode
{
public:
	BattleGridNode(const NodeData& _data) :
		 BaseNode(_data)
	{
		nodeData.isLand = true;
		debugShape = std::make_unique<sf::RectangleShape>();
		walkableArea = std::make_unique<sf::RectangleShape>();

		debugShape->setPosition(sf::Vector2f(nodeData.gridX, nodeData.gridY));
		debugShape->setSize(sf::Vector2f(nodeData.size, nodeData.size));
		debugShape->setFillColor(sf::Color::Transparent);
		debugShape->setOutlineThickness(1);
		debugShape->setOutlineColor(sf::Color::Transparent);


		walkableArea->setPosition(sf::Vector2f(nodeData.gridX, nodeData.gridY));
		walkableArea->setSize(sf::Vector2f(nodeData.size, nodeData.size));
		walkableArea->setFillColor(sf::Color(123, 123, 123, 46));
		walkableArea->setOutlineThickness(1);
		walkableArea->setOutlineColor(sf::Color(0,0,0,10));
	}

	void addNeighbour(const std::shared_ptr<BaseNode>& t_cellId, int _neighbourPos) override;

	void setAsWalkable();
	void setTransparent();

	void updateAllegiance(UnitAllegiance _allegiance);

	UnitAllegiance getCurrentAllegiance() const { return occupiedUnitAllegiance; }
	const std::vector<std::pair<std::shared_ptr<BattleGridNode>, int>>& getNeighbours();

	std::unique_ptr<sf::RectangleShape> debugShape;
	std::unique_ptr<sf::RectangleShape> walkableArea;

private:
	std::vector<std::pair<std::shared_ptr<BattleGridNode>, int>> m_neighbours;

	UnitAllegiance occupiedUnitAllegiance;
};

