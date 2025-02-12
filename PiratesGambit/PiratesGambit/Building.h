#pragma once
#include"Includes.h"
#include"TextureManager.h"
#include"HireRecruitUI.h"


class Building
{
public:
	void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;
	void RenderUI(const std::unique_ptr<sf::RenderWindow>& _window) const;
	void Update(float _dt);

	void Interact();

	void SetPosition(sf::Vector2f _pos);

	void AddParentNode(const std::shared_ptr<Node>& node) { parentNode = node; }
	void AddToOccupiedNodes(int _id) { OccupiedNodes.push_back(_id); }

	std::vector<int> GetOccupiedNodeIds() { return OccupiedNodes; }
	std::shared_ptr<Node> GetParentNode() const { return parentNode; }
protected:
	sf::Sprite buildingSprite;

	std::shared_ptr<Node> parentNode;

	std::vector<int> OccupiedNodes;
	std::unique_ptr<HireRecruitUI> buildingUI;

	int unitsAmount = 0;
};

