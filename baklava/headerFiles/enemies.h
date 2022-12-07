#pragma once
#include "raylib.h"
#include "tower.h"
#include <vector>

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
	Vector3 enemyPosition;
	EnemyWave mainwave;
};

EnemyStats generateEnemy(EnemyWave& wave);

void drawEnemy(EnemyStats stats, Color cubeColor, Color wireColor);

void killEnemy(std::vector<EnemyStats> &enemyList, TowerStats &towerStats);