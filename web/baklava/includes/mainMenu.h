#pragma once
#include "raylib.h"

/// Shows the main menu
/// 
/// Loops the main menu until the player selects something
/// @return The function returns true if the player selected to play, and false if they selected to quit out of the game
bool mainMenuLoop();

/// Transition
/// 
/// A nice transition from the main menu to the game
/// @return The function returns true if it ran successfully and false if the player quit out of the game midway
bool fadeToGame();