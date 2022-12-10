#include "raylib.h"
#include "../headerFiles/tower.h"

void drawTower(TowerStats stats)
{
	Vector3 size = stats.towerSize;
	Vector3 pos = stats.towerPos;

	DrawCube(pos, size.x, size.y, size.z, CLITERAL(Color){63, 136, 190, 255});
	DrawCubeWires(pos, size.x, size.y, size.z, CLITERAL(Color){12, 77, 105, 255});
}