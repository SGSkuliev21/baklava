#pragma once
#include "enemies.h"
#include "tower.h"
#include "raylib.h"

struct HealthBar
{
	Vector3 healthBarPosition;
	float healthBarLength;
};


HealthBar calculateHealthBar(TowerStats towerStats);

HealthBar calculateHealthBar(EnemyStats enemyStats);
