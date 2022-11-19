#pragma once
#include "raylib.h"

struct Stats 
{
	float attackSpeed;
	float attackPower;
	float defense;
	float towerHealth;
	float towerRegeneration;
};

void creteTower(Vector3 position, int* dimensions, Stats &stats, Color color, Color wireColor);
