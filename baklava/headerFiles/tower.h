#pragma once

struct TowerStats 
{
	float attackPower;
	float towerHealth;
	float towerRegen;
	int multiKill;
	Vector3 towerSize;
	Vector3 towerPos;
};

void drawTower(TowerStats stats);
