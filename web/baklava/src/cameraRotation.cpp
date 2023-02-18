#include "pch.h"

// meant to be used in a game loop
void HandleCameraRotation(Camera& camera)
{
    static float cameraRotation = 45.0f;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) cameraRotation += GetMouseDelta().x * 0.01f;
    camera.position.x = cos(cameraRotation) * 40.0f;
    camera.position.z = sin(cameraRotation) * 40.0f;
}