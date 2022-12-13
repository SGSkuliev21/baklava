#pragma once
#include "raylib.h"

struct Button
{
	Rectangle rec;
	short state;
	Color color;
	Color hoverColor;
};

/// Gives the button a state
/// 
/// The function has 4 predefined states that it can assign to a button depending on user input
/// @param button the button the function is assigning a state to
/// @see Button
void setButtonState(Button& button);

/// Changes buttons depending on their state
/// 
/// The function uses the state assigned to the buttons by setButtonState to change them visually or trigger events
/// @param button the button being changed
/// @param startWidth the original width of the button
/// @param editWidth whether or not the function should move the button around on the x axis
/// @param drawLines whether the button should have a white outline or a gray/black one
/// @return The function returns true if the button has been pressed and false otherwise
/// @see Button
bool changeButtonByState(Button& button, float startWidth, bool editWidth, bool drawLines);