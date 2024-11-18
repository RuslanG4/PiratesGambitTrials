#pragma once
#include"Includes.h"

class Camera
{
public:
	Camera()
	{
		camera.setSize(CAMERA_WIDTH, CAMERA_HEIGHT);
	}
	sf::View getCamera() const { return camera; }
	void setCameraCenter(sf::Vector2f _pos);
private:
	sf::View camera;
};

