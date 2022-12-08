#include "raylib.h"
#include <iostream>
#include "../headerFiles/healthBar.h"
#include <vector>

EnemyStats generateEnemy(EnemyWave &mainWave)
{
	EnemyStats stats;

	stats.health = mainWave.wave * 5;
	stats.damage = mainWave.wave * 2;
	stats.linePos = 15.0f;
	stats.offset = float(GetRandomValue(1, 100)) / 60.0f;
	stats.direction = GetRandomValue(-1, 2);
	stats.directionChange = GetRandomValue(1, 2);
	stats.mainwave = mainWave;

	if (stats.direction == 2) stats.direction = 0;

	if (stats.directionChange == 2) stats.directionChange = -1;

	return stats;
}


void killEnemy(std::vector<EnemyStats>& enemyList, TowerStats &towerStats)
{
	int closestEnemy[2] = {99999, 0};

	if (enemyList.size() > 0)
	{
		for (size_t i = 0; i < enemyList.size(); i++)
		{
			if (enemyList[i].linePos < closestEnemy[0])
			{
				closestEnemy[0] = enemyList[i].linePos;
				closestEnemy[1] = i;
			}
		}

		enemyList[closestEnemy[1]].health -= towerStats.attackPower;

		if (enemyList[closestEnemy[1]].health == 0)
			enemyList.erase(enemyList.begin() + closestEnemy[1]);
	}
}


void drawEnemy(EnemyStats stats, Color cubeColor, Color wireColor)
{
	float pos = stats.linePos;
	float offset = stats.offset;
	int dir = stats.direction;
	int dirChange = stats.directionChange;

	stats.enemyPosition = Vector3({ (pos * (dir)) + (offset * (dirChange * !(dir))), 0.5f, (pos * (dirChange * !(dir)) + (offset * (dir))) });

	DrawCube(stats.enemyPosition, 1.0f, 1.0f, 1.0f, cubeColor);
	DrawCubeWires(stats.enemyPosition, 1.0f, 1.0f, 1.0f, wireColor);

	HealthBar healthBarInfo = calculateHealthBar(stats);
	DrawCube(healthBarInfo.healthBarPosition, 0.5f, 0.5f, healthBarInfo.healthBarLength, CLITERAL(Color){139, 0, 0, 255});
	DrawCubeWires(healthBarInfo.healthBarPosition, 0.5f, 0.5f, healthBarInfo.healthBarLength, BROWN);
}