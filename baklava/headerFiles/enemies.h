#pragma once
#include "tower.h"
#include <vector>
#include "raylib.h"

/// Stores the wave info
struct EnemyWave
{
	int wave;
	int enemiesLeft;
};

/// Stores all enemy stats
struct EnemyStats
{
	float health = 4;
	float damage = 2;
	float linePos;
	float offset;
	int direction;
	int directionChange;
	Vector3 enemyPosition;
	EnemyWave mainwave;
};

/// Generates Enemy
/// 
/// This function generates an Enemy Stats struct for each enemy required and determines their stats based on the wave number.
/// @param wave struct which contains the wave number and enemies left on the screen
/// @return This function returns Enemy Stats struct
EnemyStats generateEnemy(EnemyWave& wave);

/// A function with is used for displaying enemies on the screen
/// 
/// This function draws enemies on the screen based on the enemy's stats
/// @param stats custam made struct with contains information about the enemy
/// @see EnemyStats(EnemyWave& wave)
void drawEnemy(EnemyStats stats);

/// Kill Enemy 
///	
/// This function kills enemies based on their position. First determines the closest enemy from the list of enemies and then subtracts from his health the tower damage.
/// @param enemyList the list with all enemies
/// @param towerStats the stats of the tower
/// @param score the player score. The score is incremented by 10 with every kill and decremented by 10 with every wrong equation.
/// @param gold the player gold. The gold is incremented by 5 with every kill
/// @see TowerStats
void killEnemy(std::vector<EnemyStats>& enemyList, TowerStats& towerStats, int& score, int& gold);