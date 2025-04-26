#include "MiniMapNode.h"

MiniMapNode::MiniMapNode(sf::Vector2f _pos, int _size)
{
	node.setSize(sf::Vector2f(_size, _size));
	node.setFillColor(sf::Color(0, 0, 0, 255)); //black
	node.setPosition(_pos);
}

void MiniMapNode::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	window->draw(node);
}

void MiniMapNode::updateColor(const std::shared_ptr<Node>& _node)
{

	switch (_node->getParentTileType())
	{
	case LAND:
		node.setFillColor(sf::Color(48, 204, 116, 255));
		break;
	case SAND:
		node.setFillColor(sf::Color(252, 236, 196, 255));
		break;
	default:
		break;
	}
	if (!_node->getIsLand()) {
		node.setFillColor(sf::Color(176, 233, 252, 255));
	}
	else if (_node->GetBuilding() != nullptr) {
		node.setFillColor(sf::Color(94, 41, 31));
	}
	else if (_node->GetObject() != nullptr && _node->GetObject()->getName() == BARREL) {
		node.setFillColor(sf::Color(120, 123, 96));
	}
}

void MiniMapNode::updatePlayerLocation()
{
	node.setFillColor(sf::Color(255, 0, 0));
}
