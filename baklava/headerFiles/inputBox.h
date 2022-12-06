#pragma once
#include "raylib.h"


struct InputBoxInfo
{
	char input[5] = {' ', ' ', ' ', ' '};
	int numCount = 0;
	Rectangle textBox;
};

void drawInputBox(InputBoxInfo &input);
int convertedPlayerAnswer(InputBoxInfo &inputBox);
