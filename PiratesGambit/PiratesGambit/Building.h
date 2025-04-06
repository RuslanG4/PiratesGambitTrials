#pragma once
#include"Includes.h"
#include"TextureManager.h"
#include"HireRecruitUI.h"
#include"BuildingPopUp.h"


class Building
{
public:
	void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;
	void Update(float _dt);

	void Interact();

	void SetPosition(sf::Vector2f _pos);

	void AddParentNode(const std::shared_ptr<Node>& node) { parentNode = node; }
	void AddToOccupiedNodes(int _id) { OccupiedNodes.push_back(_id); }

	std::vector<int> GetOccupiedNodeIds() { return OccupiedNodes; }
	std::shared_ptr<Node> GetParentNode() const { return parentNode; }

	UnitName getUnitType()const { return unitType; }
	int GetMaxUnitAmount() const { return maxUnitAmount; }

	sf::FloatRect GetHitBox()const { return myHitbox->GetGlobalBounds(); }

	bool canBuyUnits() const {
		return isActive;
	}

	void BuyUnits()
	{
		isActive = false;
		timer.restart();
	}

	float getProgressValue() const { return progress; }
protected:
	sf::Sprite buildingSprite;
	std::unique_ptr<HitBox> myHitbox;

	std::shared_ptr<Node> parentNode;

	std::vector<int> OccupiedNodes;

	UnitName unitType;
	int maxUnitAmount;

	std::unique_ptr<BuildingPopUp> popUp;
	int unitsAmount = 0;

	sf::Clock timer;
	bool isActive = true;

	float progress = 1;

	int costPerTroop;
};

