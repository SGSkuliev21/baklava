#include "raylib.h" 


struct Stats
{
	float attackSpeed;
	float attackPower;
	float defense;
	float towerHealth;
	float towerRegeneration;
};

void creteTower(Vector3 cubePosition, int *dimensions, Stats &stats, Color color, Color wireColor)
{

	int x = dimensions[0];
	int y = dimensions[1];
	int z = dimensions[2];

	DrawCube(cubePosition, x, y, z, color);
	DrawCubeWires(cubePosition, x, y, x, wireColor);
}								  