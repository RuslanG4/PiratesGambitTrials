#pragma once
#include"Includes.h"

class BattleGridNode
{
public:
	BattleGridNode(int _gridX, int _gridY, int size_) :
		gridX(_gridX),
		gridY(_gridY),
		size(size_)
	{
		debugShape = std::make_unique<sf::RectangleShape>();

		debugShape->setPosition(sf::Vector2f(gridX, gridY));
		debugShape->setSize(sf::Vector2f(size, size));
		debugShape->setFillColor(sf::Color(123, 123, 123, 46));
		debugShape->setOutlineThickness(2);
		debugShape->setOutlineColor(sf::Color::White);
	};

	void addNeighbour(const std::shared_ptr<BattleGridNode>& t_cellId);

	std::unique_ptr<sf::RectangleShape> debugShape;

	//Getters
	int getID() const { return m_id; };
	const std::vector<std::shared_ptr<BattleGridNode>>& getNeighbours() const { return m_neighbours; };
	bool isOccupied() const { return occupied; };

	sf::Vector2f getPosition() const { return { static_cast<float>(gridX), static_cast<float>(gridY) }; }
	sf::Vector2f getMidPoint() const { return  { static_cast<float>(gridX + (size / 2)), static_cast<float>(gridY + (size / 2)) }; }

	//Setters
	void setID(int _id) { m_id = _id; };
	void updateOccupied(bool _status) { occupied = _status; }

	//Resetters
	void resetMarked() { occupied = false; };

private:
	int m_id;

	int size;
	bool occupied{ false };

	std::vector<std::shared_ptr<BattleGridNode>> m_neighbours;
	//							    3  	
	// structure of neighbours -> 1 X 7
	//							    5  

	int gridX; //position x
	int gridY; //position y
};

