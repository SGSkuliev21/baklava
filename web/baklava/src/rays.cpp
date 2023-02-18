#include "pch.h"

TowerRay createRay(Vector3 enemyPos)
{
	TowerRay temp;

	temp.origin = Vector3({ 0, 7, 0 });
	temp.target = enemyPos;
	temp.lifespan = 12;
	
	return temp;
}

bool drawRay(TowerRay& ray)
{
	DrawLine3D(ray.origin, ray.target, DARKPURPLE);
	DrawLine3D(Vector3({ ray.origin.x + 0.2f, ray.origin.y, ray.origin.z }), ray.target, DARKPURPLE);
	DrawLine3D(Vector3({ ray.origin.x - 0.2f, ray.origin.y, ray.origin.z }), ray.target, DARKPURPLE);
	DrawLine3D(Vector3({ ray.origin.x, ray.origin.y, ray.origin.z + 0.2f }), ray.target, DARKPURPLE);
	DrawLine3D(Vector3({ ray.origin.x, ray.origin.y, ray.origin.z + 0.2f }), ray.target, DARKPURPLE);

	ray.lifespan--;
	if (ray.lifespan == 0) return true;
	else return false;
}