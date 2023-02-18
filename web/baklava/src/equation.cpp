#include "pch.h"


Equation generateEquation()
{
	Equation equationInfo;

	equationInfo.firstNumber = GetRandomValue(0,10);
	equationInfo.secondNumber = GetRandomValue(0,10);
	
	int operation = GetRandomValue(0, 2);

	switch (operation)
	{
		case 0:
            equationInfo.answer = equationInfo.firstNumber + equationInfo.secondNumber; equationInfo.operation = '+';
			break;
		case 1:
			equationInfo.answer = equationInfo.firstNumber - equationInfo.secondNumber; equationInfo.operation = '-';
			break;
		case 2:
			equationInfo.answer = equationInfo.firstNumber * equationInfo.secondNumber; equationInfo.operation = '*';
			break;
	}

	return equationInfo;
};

void equationHandler(InputBoxInfo& inputBox, Equation& equation, TowerStats towerStats, EnemyWave& wave, std::vector<EnemyStats>& enemyList, std::vector<TowerRay>& rayList, int& score, int& gold)
{
    int playerAnswer = convertedPlayerAnswer(inputBox);

    if (equation.answer == playerAnswer)
    {
        score += 5;

        for (size_t i = 0; i < 4; i++)
        {
            inputBox.input[i] = ' ';
        }
        inputBox.numCount = 0;

        for (size_t i = 0; i < towerStats.multiKill; i++)
        {
            killEnemy(wave, enemyList, rayList, towerStats, score, gold);
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

void drawEquation(Equation& equation, Font& font)
{
    //Draw box
    DrawRectangleRec(Rectangle{ 920, 40, 300, 90 }, RAYWHITE);

    //Draw border
    DrawRectangleLinesEx(Rectangle{ 920, 40, 300, 90 }, 4, BLACK);

    //Draw Equation
    DrawTextEx(font, TextFormat("%i %c %i = ", equation.firstNumber, equation.operation, equation.secondNumber), Vector2({ 940, 56 }), 52, 0, BLACK);
}