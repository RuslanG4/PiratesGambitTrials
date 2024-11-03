#include "FullMap.h"

FullMap::FullMap(sf::RenderWindow& window, TextureManager& instance)
{
	int iteration = 0;
	int rand = std::rand() % 35+15;
	int iterss = std::rand() % 4;
	//for(int y= 0 ; y < 3; y++) //whole map is 3x3
	//{
	//	for(int x=0;x<3;x++)
	//	{
	//		int height = 576;/* 16 * ((std::rand() % 16  + 16) + 16);*/
	//		int width = 576;/*16 * ((std::rand() % 16+16) + 16);*/
	//		iteration++;
	//		if(iteration == 2 || iteration == 4 || iteration ==9)
	//		{
	//			Grid* chunk = new Grid(70, sf::Vector2f(x * width, y * height), width, height);
	//			chunk->ApplyCellular(7, window);
	//			chunks_.push_back(chunk);
	//		}else
	//		{
	//			Grid* chunk = new Grid(52, sf::Vector2f(x * width, y * height), width, height);
	//			chunk->ApplyCellular(3, window);
	//			chunks_.push_back(chunk);
	//		}
	//	}
	//}
	int height = 1024;/* 16 * ((std::rand() % 16  + 16) + 16);*/
	int width = 1024;/*16 * ((std::rand() % 16+16) + 16);*/
	Grid* chunk = new Grid(70, sf::Vector2f(0 * width, 0 * height), width, height, instance);
	chunk->ApplyCellular(7, window);
	chunks_.push_back(chunk);

	//Grid* chunk = new Grid();
	//chunk->DiamondSquare();
	//chunks_.push_back(chunk);

}

void FullMap::render(sf::RenderWindow& window)
{
	for(auto chunk : chunks_)
	{
		chunk->drawGrid(window);
	}
}
