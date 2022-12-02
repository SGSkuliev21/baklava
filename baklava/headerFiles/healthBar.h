#pragma once
#include "raylib.h"
#include "enemies.h"
#include "tower.h"

struct HealthBar
{
	Vector3 healthBarPosition;
	float healthBarLength;
};


HealthBar calculateHealthBar(TowerStats towerStats);

HealthBar calculateHealthBar(EnemyStats enemyStats);
