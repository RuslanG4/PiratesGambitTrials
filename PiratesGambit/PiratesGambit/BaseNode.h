#pragma once
#include"Includes.h"
#include "Structs.h"


class BaseNode
{
public:
	BaseNode(const NodeData& _data) : nodeData(_data){}

	virtual void addNeighbour(const std::shared_ptr<BaseNode>& t_cellId, int _neighbourPos) = 0;
	virtual void setPrevious(const std::shared_ptr<BaseNode>& _previous) = 0;

	//Getters
	int getID() const { return  nodeData.m_id; }
	bool isOccupied() const { return  nodeData.occupied; }
	bool hasBeenTraversed() const { return  nodeData.traversed; }
	sf::Vector2f getMovementVector() const { return movementVector; }
	NodeData getNodeData() const { return nodeData; }

	sf::Vector2f getPosition() const { return { static_cast<float>(nodeData.gridX), static_cast<float>(nodeData.gridY) }; }
	sf::Vector2f getMidPoint() const { return  { static_cast<float>(nodeData.gridX + (nodeData.size / 2)), static_cast<float>(nodeData.gridY + (nodeData.size / 2)) }; }

	//Setters
	void setID(int _id) { nodeData.m_id = _id; };
	void updateOccupied(bool _status) { nodeData.occupied = _status; }
	void updateTraversed(bool _status) { nodeData.traversed = _status; }

	void setMovementVector(sf::Vector2f _vec) { movementVector = _vec; }

	void setFCost(int _cost) { nodeData.fCost = _cost; }
	void setGCost(int _cost) { nodeData.gCost = _cost; }
	void setHCost(int _cost) { nodeData.hCost = _cost; }

	//Resetters
	void resetMarked() { nodeData.occupied = false; };
protected:
	~BaseNode() = default;
	NodeData nodeData;
	sf::Vector2f movementVector{0,0};
private:
};

