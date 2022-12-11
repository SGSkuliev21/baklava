#pragma once
#include "raylib.h"

bool mainMenuLoop();

struct Button
{
	Rectangle rect;
	short state;
	Color color;
	Color hoverColor;
};
