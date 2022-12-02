#pragma once
#include "raylib.h"

struct EnemyWave
{
	int wave;
	int enemiesLeft;
};

struct EnemyStats
{
	float health;
	float damage;
	float linePos;
	float offset;
	int direction;
	int directionChange;
	Vector3 EnemyPosition;
	EnemyWave mainwave;
};

EnemyStats generateEnemy(EnemyWave& wave);

void drawEnemy(EnemyStats stats, Color cubeColor, Color wireColor);