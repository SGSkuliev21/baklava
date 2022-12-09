#pragma once
#include "tower.h"
#include <vector>
#include "raylib.h"

struct EnemyWave
{
	int wave;
	int enemiesLeft;
};

struct EnemyStats
{
	float health = 4;
	float damage = 2;
	float linePos;
	float offset;
	int direction;
	int directionChange;
	Vector3 enemyPosition;
	EnemyWave mainwave;
};

EnemyStats generateEnemy(EnemyWave& wave);

void drawEnemy(EnemyStats stats, Color cubeColor, Color wireColor);

void killEnemy(std::vector<EnemyStats> &enemyList, TowerStats &towerStats, int &score, int &gold);