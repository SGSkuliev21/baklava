#pragma once
#include "raylib.h"

struct TowerStats 
{
	float attackPower;
	float defense;
	float towerHealth;
	float towerRegen;
	Vector3 towerSize;
	Vector3 towerPos;
};

void drawTower(TowerStats stats, Color color, Color wireColor);
