#include "raylib.h"
#include "../headerFiles/healthBar.h" 

void drawTower(TowerStats stats)
{
	Vector3 size = stats.towerSize;
	Vector3 pos = stats.towerPos;

	DrawCube(pos, size.x, size.y, size.z, CLITERAL(Color){63, 136, 190, 255});
	DrawCubeWires(pos, size.x, size.y, size.z, CLITERAL(Color){12, 77, 105, 255});

	HealthBar healthBarInfo = calculateHealthBar(stats);
	DrawCube(healthBarInfo.healthBarPosition, 0.5f, 0.5f, healthBarInfo.healthBarLength, CLITERAL(Color){0, 158, 0, 255});
	DrawCubeWires(healthBarInfo.healthBarPosition, 0.5f, 0.5f, healthBarInfo.healthBarLength, CLITERAL(Color){0, 89, 0, 255});
}