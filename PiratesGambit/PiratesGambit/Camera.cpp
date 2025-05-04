#include "Camera.h"

void Camera::handleZooming(sf::Event event)
{
    if (event.type == sf::Event::MouseWheelScrolled) {
        float zoomFactor = (event.mouseWheelScroll.delta > 0) ? 0.9f : 1.1f;
        float newZoomLevel = zoomLevel * zoomFactor;

        // Apply zoom only if within limits
        if (newZoomLevel >= minZoom && newZoomLevel <= maxZoom) {
            camera.zoom(zoomFactor);
            zoomLevel = newZoomLevel;
        }
    }
}

void Camera::shakeCamera(sf::Vector2f direction)
{
    shakeStartOffset = (-direction * 15.f);
    shakeTargetOffset = { 0.f, 0.f };
    shakeClock.restart();
    isShaking = true;
}

void Camera::update(sf::Vector2f playerPos, sf::Vector2f _worldSize)
{
    sf::Vector2f cameraPos = camera.getCenter();
    sf::Vector2f cameraSize = camera.getSize();

    float minX = cameraSize.x / 2.0f;
    float maxX = _worldSize.x - cameraSize.x / 2.0f;
    float minY = cameraSize.y / 2.0f;
    float maxY = _worldSize.y - cameraSize.y / 2.0f;

    float borderMarginX = 10.0f; 
    float borderMarginY = 10.0f; 

    sf::Vector2f targetCameraPos = playerPos;

    targetCameraPos.x = std::clamp(targetCameraPos.x, minX + borderMarginX, maxX - borderMarginX);
    targetCameraPos.y = std::clamp(targetCameraPos.y, minY + borderMarginY, maxY - borderMarginY);

    sf::Vector2f finalOffset = { 0.f, 0.f };

    if (isShaking)
    {
        float time = shakeClock.getElapsedTime().asSeconds() / totalShakeDuration;

        if (time >= 1.0f)
            isShaking = false;
        else
            finalOffset = shakeStartOffset * (1.0f - time); //lerp
    }

    camera.setCenter(targetCameraPos + finalOffset);
}
