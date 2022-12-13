#include <cmath>
#include "raylib.h"

// meant to be used in a game loop
void HandleCameraRotation(Camera& camera)
{
    static float cameraRotation = 45.f;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) cameraRotation += GetMouseDelta().x * .01f;
    camera.position.x = cos(cameraRotation) * 40.f;
    camera.position.z = sin(cameraRotation) * 40.f;
}