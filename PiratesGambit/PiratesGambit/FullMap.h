#pragma once
#include"Grid.h"

class FullMap
{
public:
	FullMap(sf::RenderWindow & window, TextureManager& instance);
	~FullMap();

	void update();
	void render(sf::RenderWindow& window);

	std::vector<Grid*> getChunks() { return chunks_; };
private:
	std::vector<Grid*> chunks_;
};

