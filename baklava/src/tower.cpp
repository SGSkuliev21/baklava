#include "raylib.h"
#include "../headerFiles/healthBar.h" 

void drawTower(TowerStats stats, Color color, Color wireColor)
{
	Vector3 size = stats.towerSize;
	Vector3 pos = stats.towerPos;

	DrawCube(pos, size.x, size.y, size.z, color);
	DrawCubeWires(pos, size.x, size.y, size.z, wireColor);

	HealthBar healthBarInfo = calculateHealthBar(stats);
	DrawCube(healthBarInfo.healthBarPosition, 0.5f, 0.5f, healthBarInfo.healthBarLength, GREEN);
	DrawCubeWires(healthBarInfo.healthBarPosition, 0.5f, 0.5f, healthBarInfo.healthBarLength, DARKGREEN);
}