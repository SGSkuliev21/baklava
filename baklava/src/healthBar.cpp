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