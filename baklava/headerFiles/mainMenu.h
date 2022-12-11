#pragma once
#include "raylib.h"

bool mainMenuLoop();

struct Button
{
	Rectangle rec;
	short state;
	Color color;
	Color hoverColor;
};
