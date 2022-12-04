#include "raylib.h"
#include "../headerFiles/equation.h"

void stringify(char* equation)
{
	for (size_t i = 0; i < 30; i++)
	{


	}
}

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
