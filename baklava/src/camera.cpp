#include "raylib.h"

void cameraSetUp(Camera& camera, float FOV, Vector3 position, Vector3 target)
{
	camera.position =  position;
	camera.target = target;
	camera.up = Vector3({ 0.0f, 1.0f, 0.0f });
	camera.fovy = FOV;
}