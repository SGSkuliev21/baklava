#pragma once
#include "raylib.h"


struct InputBoxInfo
{
	char input[4] = {' ', ' ', ' '};
	int numCount = 0;
	Rectangle textBox;
};

void drawInputBox(InputBoxInfo &input);
