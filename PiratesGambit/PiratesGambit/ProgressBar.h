#pragma once
#include"Includes.h"
class ProgressBar
{
public:
	ProgressBar(sf::Vector2f _pos);
	void Render(const std::unique_ptr<sf::RenderWindow>& _win) const;

	void PassProgress(float progress);

private:
	sf::RectangleShape backgroundBar;
	sf::RectangleShape progressBar;
};

