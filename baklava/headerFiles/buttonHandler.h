#pragma once
#include "raylib.h"

struct Button
{
	Rectangle rec;
	short state;
	Color color;
	Color hoverColor;
};


void setButtonState(Button& button);

bool changeButtonByState(Button& button, float startWidth, bool editWidth, bool drawLines);