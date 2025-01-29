#pragma once
#include"Includes.h"
#include"TextureManager.h"
#include"HireRecruitUI.h"


class Building
{
public:
	void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;
	void Update();

	void Interact();

	void SetPosition(sf::Vector2f _pos);
	void AddToOccupiedNodes(int _id) { OccupiedNodes.push_back(_id); }

	std::vector<int> GetOccupiedNodeIds() { return OccupiedNodes; }
protected:
	sf::Sprite buildingSprite;

	std::vector<int> OccupiedNodes;
	std::unique_ptr<HireRecruitUI> buildingUI;
};

