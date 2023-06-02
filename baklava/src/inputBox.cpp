#include "pch.h"


void drawInputBox(InputBoxInfo& inputBox, Equation& equation, Font& font)
{
		int pressedKey = GetCharPressed();

		//Checking if multiple character have been pressed at the same time
		while (pressedKey > 0)
		{
			if ((pressedKey == 45) || (pressedKey >= 48) && (pressedKey <= 57) && (inputBox.numCount < 4))
			{
				inputBox.input[inputBox.numCount] = (char)(pressedKey);
				inputBox.input[inputBox.numCount + 1] = '\0';
				inputBox.numCount++;
			}

			pressedKey = GetCharPressed(); // Getting the next character
		}

		if (IsKeyPressed(KEY_BACKSPACE))
		{
			inputBox.numCount--;
			if (inputBox.numCount < 0) inputBox.numCount = 0;
			inputBox.input[inputBox.numCount] = '\0';
		}

		Vector2 textPos = Vector2{ inputBox.textBox.x + MeasureTextEx(font, TextFormat("%i %c %i", equation.firstNumber, equation.operation, equation.secondNumber), 54, 0).x - 10.0f, inputBox.textBox.y };

		DrawTextEx(font, inputBox.input, textPos, 52, 0, BLACK);

}


int convertedPlayerAnswer(InputBoxInfo &inputBox)
{
	if (inputBox.input[0] == '-')
	{
		switch (inputBox.numCount)
		{
			case 4:
				return (((int)inputBox.input[1] - '0') * 100 + ((int)inputBox.input[2] - '0') * 10 + (int)inputBox.input[3] - '0') * -1;
				break;
			case 3:
				return (((int)inputBox.input[1] - '0') * 10 + (int)inputBox.input[2] - '0') * -1;
				break;
			case 2:
				return ((int)inputBox.input[1] - '0') * -1;
				break;
			default:
				return 1000;
		}
	}
	else
	{
		switch (inputBox.numCount)
		{
			case 3:
				return ((int)inputBox.input[0] - '0') * 100 + ((int)inputBox.input[1] - '0') * 10 + (int)inputBox.input[2] - '0';
				break;
			case 2:
				return ((int)inputBox.input[0] - '0') * 10 + (int)inputBox.input[1] - '0';
				break;
			case 1:
				return (int)inputBox.input[0] - '0';
				break;
			default:
				 return 1000;
		}
	}
}