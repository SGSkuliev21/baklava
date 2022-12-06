#include "raylib.h"
#include <iostream>
#include "../headerFiles/equation.h"


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

