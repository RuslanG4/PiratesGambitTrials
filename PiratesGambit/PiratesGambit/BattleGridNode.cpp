#include "BattleGridNode.h"

void BattleGridNode::addNeighbour(const std::shared_ptr<BaseNode>& t_cellId, int _neighbourPos)
{
    if (auto battleNeighbour = std::dynamic_pointer_cast<BattleGridNode>(t_cellId)) {
        m_neighbours.emplace_back(battleNeighbour, _neighbourPos);
    }
    else {
        std::cout << "Error wrong node passed in";
    }
}

void BattleGridNode::setPrevious(const std::shared_ptr<BaseNode>& _previous)
{
    if (auto battlePrevious = std::dynamic_pointer_cast<BattleGridNode>(_previous)) {
        previousNode = battlePrevious;
    }
    else {
        std::cout << "Error wrong node passed in";
    }
}

void BattleGridNode::setAsWalkable()
{
    debugShape->setFillColor(sf::Color(76, 138, 14, 128));
    debugShape->setOutlineColor(sf::Color(37, 69, 5, 128));
}

void BattleGridNode::setTransparent()
{
    debugShape->setFillColor(sf::Color::Transparent);
    debugShape->setOutlineColor(sf::Color::Transparent);
}

void BattleGridNode::updateAllegiance(UnitAllegiance _allegiance)
{
    occupiedUnitAllegiance = _allegiance;
}

const std::vector<std::pair<std::shared_ptr<BattleGridNode>, int>>& BattleGridNode::getNeighbours()
{
    return m_neighbours;
}

const std::shared_ptr<BattleGridNode>& BattleGridNode::getPrevious()
{
    return previousNode;
}
