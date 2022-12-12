#pragma once
#include "raylib.h"
#include "enemies.h"

struct TowerRay
{
	Vector3 origin;
	Vector3 target;
	int lifespan;
};

TowerRay createRay(Vector3 enemyPos);

bool drawRay(TowerRay& ray);