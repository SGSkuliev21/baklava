#include "raylib.h"
#include "../headerFiles/tower.h"

void drawTower(TowerStats &stats)
{
	Vector3 size = stats.towerSize;
	Vector3 pos = stats.towerPos;

	DrawCubeV(pos, size, CLITERAL(Color){63, 136, 190, 255});
	DrawCubeWiresV(pos, size, CLITERAL(Color){12, 77, 105, 255});
}