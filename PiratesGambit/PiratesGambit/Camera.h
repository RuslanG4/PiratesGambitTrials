#pragma once
#include "Includes.h"

/// <summary>
/// Singleton class that manages the camera (view) in the game.
/// Responsible for handling the camera's position and size.
/// </summary>
class Camera
{
public:
    /// <summary>
    /// Retrieves the singleton instance of the Camera.
    /// Ensures that only one camera instance exists.
    /// </summary>
    /// <returns>Reference to the Camera instance.</returns>
    static Camera& getInstance()
    {
        static Camera instance;
        return instance;
    }

    /// <summary>
    /// Deleted copy constructor to prevent copying of the singleton instance.
    /// </summary>
    Camera(const Camera&) = delete;

    /// <summary>
    /// Deleted assignment operator to prevent copying of the singleton instance.
    /// </summary>
    Camera& operator=(const Camera&) = delete;

    /// <summary>
    /// Retrieves the current SFML view representing the camera.
    /// </summary>
    /// <returns>The SFML view (camera).</returns>
    sf::View getCamera() const { return camera; }

    /// <summary>
    /// Sets the center position of the camera.
    /// </summary>
    /// <param name="_pos">New position for the camera center.</param>
    void setCameraCenter(sf::Vector2f _pos) { camera.setCenter(_pos); }

    void handleZooming(sf::Event event);

    void update(sf::Vector2f playerPos, sf::Vector2f _worldSize);

private:
    /// <summary>
    /// Private constructor to enforce the singleton pattern.
    /// Initializes the camera with a predefined width and height.
    /// </summary>
    Camera()
    {
        camera.setSize(CAMERA_WIDTH, CAMERA_HEIGHT);
    }

    sf::View camera; ///< SFML view representing the camera.

    float zoomLevel = 1.0f;  ///< Current zoom level
    const float minZoom = 1.f;  ///< Minimum zoom level (zoomed in)
    const float maxZoom = 2.0f;  ///< Maximum zoom level (zoomed out)
};
