#include "raylib.h" 
#include "../headerFiles/enemies.h"
#include "../headerFiles/tower.h"

struct HealthBar
{
	Vector3 healthBarPosition;
	float healthBarLength;
};


HealthBar calculateHealthBar(TowerStats towerStats)
{
	HealthBar healthBarInfo;

	healthBarInfo.healthBarPosition.x = towerStats.towerPos.x + 0.25f;
	healthBarInfo.healthBarPosition.y = towerStats.towerPos.y + 5.0f;
	healthBarInfo.healthBarPosition.z = towerStats.towerPos.z + 0.35f;

	healthBarInfo.healthBarLength = (float)towerStats.towerHealth / 30.0f;

	return healthBarInfo;
}

HealthBar calculateHealthBar(EnemyStats enemyStats)
{
	HealthBar healthBarInfo;

	healthBarInfo.healthBarPosition.x = enemyStats.enemyPosition.x + 0.25f;
	healthBarInfo.healthBarPosition.y = enemyStats.enemyPosition.y + 1.0f;
	healthBarInfo.healthBarPosition.z = enemyStats.enemyPosition.z + 0.35f;

	healthBarInfo.healthBarLength = (float)enemyStats.health / (float)(enemyStats.mainwave.wave * 2.5f);

	return healthBarInfo;
}