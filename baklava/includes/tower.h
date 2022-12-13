#pragma once

/// Stores the stats for the tower
struct TowerStats 
{
	float attackPower;
	float towerHealth;
	float towerRegen;
	int multiKill;
	Vector3 towerSize;
	Vector3 towerPos;
};

/// Display the tower on the screen
/// 
/// This function displayes the tower on the screen based on the stats
/// @param stats the tower stats
/// @see TowerStats
void drawTower(TowerStats& stats);
