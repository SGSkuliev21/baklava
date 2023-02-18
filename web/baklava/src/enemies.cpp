#include "pch.h"

EnemyStats generateEnemy(EnemyWave &mainWave)
{
	EnemyStats stats;

	switch (mainWave.wave) 
	{
		case 2: case 3: case 4:
			stats.health += mainWave.wave * 1.5f;
			stats.damage += mainWave.wave * 1.3f;
			break;
		case 5: case 6: case 7:
			stats.health += mainWave.wave * 2.3f;
			stats.damage += mainWave.wave * 2.0f;
			break;
		case 8: case 9: case 10:
			stats.health += mainWave.wave * 4.0f;
			stats.damage += mainWave.wave * 3.5f;
			break;
	}

	stats.linePos = 15.0f;
	stats.offset = float(GetRandomValue(1, 100)) / 60.0f;
	stats.direction = GetRandomValue(-1, 2);
	stats.directionChange = GetRandomValue(1, 2);
	stats.mainwave = mainWave;

	if (stats.direction == 2) stats.direction = 0;

	if (stats.directionChange == 2) stats.directionChange = -1;

	return stats;
}

void waveSpawnHandler(int& debounce, const int enemyLimit, EnemyWave& wave, std::vector<EnemyStats>& enemyList, int& waveTimer, const int fps)
{
	if (wave.enemiesLeft > 0 && wave.wave <= 10 && waveTimer == 0)
	{
		if (enemyList.size() <= enemyLimit && debounce == 0)
		{
			enemyList.push_back(generateEnemy(wave));

			debounce = 0.8 * fps;
			wave.enemiesLeft--;
		}
		debounce--;
	}
	else if(waveTimer <= 0 && wave.enemiesLeftAlive == 0)
	{
		wave.wave++;
		waveTimer = 2 * fps;
		wave.enemiesLeft = 6;
		wave.enemiesLeftAlive = wave.enemiesLeft;
	}
	else
	{
		waveTimer--;
	}
}

void drawEnemy(EnemyStats& stats)
{
	float pos = stats.linePos;
	float offset = stats.offset;
	int dir = stats.direction;
	int dirChange = stats.directionChange;

	stats.enemyPosition = Vector3({ (pos * (dir)) + (offset * (dirChange * !(dir))), 0.5f, (pos * (dirChange * !(dir)) + (offset * (dir))) });

	DrawCube(stats.enemyPosition, 1.0f, 1.0f, 1.0f, CLITERAL(Color){189, 0, 0, 255});
	DrawCubeWires(stats.enemyPosition, 1.0f, 1.0f, 1.0f, CLITERAL(Color){150, 0, 0, 255});
}

void killEnemy(EnemyWave& wave, std::vector<EnemyStats>& enemyList, std::vector<TowerRay>& rayList, TowerStats &towerStats, int &score, int &gold)
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

		rayList.push_back(createRay(enemyList[closestEnemy[1]].enemyPosition));

		enemyList[closestEnemy[1]].health -= towerStats.attackPower;

		if (enemyList[closestEnemy[1]].health < 0)
		{ 
			wave.enemiesLeftAlive--;
			enemyList.erase(enemyList.begin() + closestEnemy[1]);
			score += 5;
			gold += 5;
		}
	}
}