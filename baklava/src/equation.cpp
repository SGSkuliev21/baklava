#include "raylib.h"
#include <vector>
#include "../headerFiles/equation.h"
#include "../headerFiles/inputBox.h"
#include "../headerFiles/tower.h"
#include "../headerFiles/enemies.h"


Equation generateEquation()
{
	Equation equationInfo;

	equationInfo.firstNumber = GetRandomValue(0,10);
	equationInfo.secondNumber = GetRandomValue(0,10);
	
	equationInfo.operation = GetRandomValue(0, 2);

	switch (equationInfo.operation)
	{
		case 0:
			equationInfo.answer = equationInfo.firstNumber + equationInfo.secondNumber;
			break;
		case 1:
			equationInfo.answer = equationInfo.firstNumber - equationInfo.secondNumber;
			break;
		case 2:
			equationInfo.answer = equationInfo.firstNumber * equationInfo.secondNumber;
			break;
	}

	return equationInfo;
};

void equationHandler(InputBoxInfo& inputBox, Equation& equation, TowerStats towerStats, EnemyWave& wave, std::vector<EnemyStats>& enemyList, int& score, int& gold)
{
    int playerAnswer = convertedPlayerAnswer(inputBox);

    if (equation.answer == playerAnswer)
    {
        for (size_t i = 0; i < 4; i++)
        {
            inputBox.input[i] = ' ';
        }
        inputBox.numCount = 0;

        for (size_t i = 0; i < towerStats.multiKill; i++)
        {
            killEnemy(wave, enemyList, towerStats, score, gold);
        }
    }
    else
    {
        for (size_t i = 0; i < 4; i++)
        {
            inputBox.input[i] = ' ';
        }
        inputBox.numCount = 0;

        if (score > 0)
            score -= 10;
    }

    equation = generateEquation();
}