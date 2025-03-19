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
