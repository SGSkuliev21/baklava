#include "raylib.h"
#include "../headerFiles/inputBox.h"


void drawInputBox(InputBoxInfo &inputBox)
{
		int pressedKey = GetCharPressed();

		//Checking if multiple character have been pressed at the same time
		while (pressedKey > 0)
		{
			if ((pressedKey >= 48) && (pressedKey <= 57) && (inputBox.numCount < 3))
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

	DrawRectangleRec(inputBox.textBox, LIGHTGRAY);
	DrawText(inputBox.input, (int)inputBox.textBox.x + 4, (int)inputBox.textBox.y + 4, 30, BLACK);

}