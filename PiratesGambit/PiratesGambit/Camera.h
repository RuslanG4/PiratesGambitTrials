#pragma once
#include"Includes.h"

class Camera
{
public:
    static Camera& getInstance()
    {
        static Camera instance;
        return instance;
    }

    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;

    sf::View getCamera() const { return camera; }
    void setCameraCenter(sf::Vector2f _pos) { camera.setCenter(_pos); }

private:
    Camera()
    {
        camera.setSize(CAMERA_WIDTH, CAMERA_HEIGHT);
    }

    sf::View camera;
};


