#pragma once
#include "inputBox.h"
#include "tower.h"
#include "enemies.h"
#include "rays.h"

/// Stores all equation info
struct Equation
{
	int firstNumber = 0;
	int secondNumber = 0;
	int operation = 0;
	int answer = 0;
};

/// Generates an equation
/// 
/// This function generates equation randomlly by picking two number between 0, 10 and an operator. The operator can be 0(+), 1(-), 2(*). And based on the numbers and operator generates the answer.
/// @return Equation struct
/// @see Equation
Equation generateEquation();


void equationHandler(InputBoxInfo& inputBox, Equation& equation, TowerStats towerStats, EnemyWave& wave, std::vector<EnemyStats>& enemyList, std::vector<TowerRay>& rayList, int& score, int& gold);