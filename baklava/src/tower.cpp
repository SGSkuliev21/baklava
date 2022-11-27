#include "raylib.h"

struct TowerStats
{
	float attackSpeed;
	float attackPower;
	float defense;
	float towerHealth;
	float towerRegen;
	Vector3 towerSize;
	Vector3 towerPos;
};

void drawTower(TowerStats stats, Color color, Color wireColor)
{
	Vector3 size = stats.towerSize;
	Vector3 pos = stats.towerPos;

	DrawCube(pos, size.x, size.y, size.z, color);
	DrawCubeWires(pos, size.x, size.y, size.z, wireColor);
}