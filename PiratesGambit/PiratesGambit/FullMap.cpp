#include "FullMap.h"

FullMap::FullMap(sf::RenderWindow& window)
{
	int iteration = 0;
	//for(int y= 0 ; y < 5; y++) //whole map is 3x3
	//{
	//	for(int x=0;x<5;x++)
	//	{
	//		iteration++;
	//		if(iteration % 3 == 0)
	//		{
	//			/*Grid* chunk = new Grid(70, sf::Vector2f(x * SCREEN_WIDTH, y * SCREEN_HEIGHT));
	//			chunk->ApplyCellular(8, window);
	//			chunks_.push_back(chunk);*/
	//			Grid* chunk = new Grid(68, sf::Vector2f(x * SCREEN_WIDTH, y * SCREEN_HEIGHT));
	//			chunk->ApplyCellular(8, window);
	//			chunks_.push_back(chunk);
	//		}else
	//		{
	//			Grid* chunk = new Grid(45, sf::Vector2f(x * SCREEN_WIDTH, y * SCREEN_HEIGHT));
	//			chunk->ApplyCellular(5, window);
	//			chunks_.push_back(chunk);
	//		}
	//		
	//	}
	//}
	Grid* chunk = new Grid(67, sf::Vector2f(0 * SCREEN_WIDTH, 0 * SCREEN_HEIGHT));
	chunk->ApplyCellular(7, window);
	chunks_.push_back(chunk);
}

void FullMap::render(sf::RenderWindow& window)
{
	for(auto chunk : chunks_)
	{
		chunk->drawGrid(window);
	}
}
