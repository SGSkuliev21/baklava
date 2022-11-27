#include "raylib.h"

struct EnemyWave
{
	int wave;
	int enemiesLeft;
};

struct EnemyStats
{
	float health;
	float damage;
	float linePos;
	float offset;
	int direction;
	int directionChange;
};

EnemyStats generateEnemy(EnemyWave& mainWave)
{
	EnemyStats stats;

	stats.health = mainWave.wave * 5;
	stats.damage = mainWave.wave * 2;
	stats.linePos = 10.0f;
	stats.offset = float(GetRandomValue(1, 100)) / 60.0f;
	stats.direction = GetRandomValue(-1, 2);
	stats.directionChange = GetRandomValue(1, 2);

	if (stats.direction == 2) stats.direction = 0;
	if (stats.direction == 1 + stats.direction)
	{
		stats.direction *= -1;
		stats.direction += 1;
	}

	if (stats.directionChange == 2) stats.directionChange = -1;

	return stats;
}

void drawEnemy(EnemyStats stats, Color cubeColor, Color wireColor)
{
	float pos = stats.linePos;
	float offset = stats.offset;
	int dir = stats.direction;
	int dirChange = stats.directionChange;

	DrawCube(Vector3({ (pos * (dir)) + (offset * (dirChange * !(dir))), 0.5f, (pos * (dirChange * !(dir)) + (offset * (dir))) }), 1.0f, 1.0f, 1.0f, cubeColor);
	DrawCubeWires(Vector3({ (pos * (dir)) + (offset * (dirChange * !(dir))), 0.5f, (pos * (dirChange * !(dir)) + (offset * (dir))) }), 1.0f, 1.0f, 1.0f, wireColor);
}