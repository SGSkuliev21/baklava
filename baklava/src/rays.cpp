#include "raylib.h"
#include <cmath>
#include "../headerFiles/tower.h"
#include "../headerFiles/enemies.h"
#include "../headerFiles/rays.h"

TowerRay createRay(Vector3 enemyPos)
{
	TowerRay temp;

	temp.origin = Vector3({ 0, 7, 0 });
	temp.target = enemyPos;
	temp.lifespan = 0.2f * GetFPS();
	
	return temp;
}

bool drawRay(TowerRay& ray)
{
	DrawLine3D(ray.origin, ray.target, DARKPURPLE);
	ray.lifespan--;
	if (ray.lifespan == 0) return true;
	else return false;
}