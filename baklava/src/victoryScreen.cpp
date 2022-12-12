#include "raylib.h"
#include "../headerFiles/buttonHandler.h"

bool showVictoryScreen()
{
	//Load font and configure upscaling
	Font mainFont = LoadFontEx("assets/fonts/MainFont.ttf", 54, NULL, 0);
	SetTextureFilter(mainFont.texture, TEXTURE_FILTER_BILINEAR);

	//Declare the play button
	Button playButton;
	playButton.rec = { 235, 431, 292, 113 };
	playButton.state = 0;
	playButton.color = CLITERAL(Color) { 194, 51, 51, 255 };
	playButton.hoverColor = CLITERAL(Color) { 164, 21, 21, 255 };
	Vector2 playButtonSize = MeasureTextEx(mainFont, "Play Again", 54, 0);
	
	//Declare the quit button
	Button quitButton;
	quitButton.rec = { 753, 431, 292, 113 };
	quitButton.state = 0;
	quitButton.color = CLITERAL(Color) { 158, 47, 197, 255 };
	quitButton.hoverColor = CLITERAL(Color) { 138, 17, 167, 255 };
	Vector2 quitButtonSize = MeasureTextEx(mainFont, "Quit", 54, 0);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		//Clear the image
		ClearBackground(RAYWHITE);

		//Draw the background gradient
		DrawRectangleGradientH(0, 0, 1280, 720, CLITERAL(Color){2, 171, 58, 255}, CLITERAL(Color) { 1, 97, 33, 255 });
		DrawRectangleGradientV(0, 0, 1280, 720, CLITERAL(Color){ 2, 171, 58, 123 }, CLITERAL(Color) { 1, 97, 33, 123 });
		DrawRectangleLinesEx(Rectangle({ 164, 92, 953, 536 }), 10,  RAYWHITE);

		//Draw the title
		DrawTextEx(mainFont, "You won!", Vector2({ 640 - MeasureTextEx(mainFont, "You won!", 54, 0).x / 2, 152 }), 54, 0, RAYWHITE);

		//Get the state of each button
		setButtonState(playButton);
		setButtonState(quitButton);

		//Act according to user actions
		if (changeButtonByState(playButton, 292, true))
		{
			return true;
		}
		if (changeButtonByState(quitButton, 292, true)) return false;

		//Draw text over buttons
		DrawTextEx(mainFont, "Play Again", Vector2({ (playButton.rec.x + (playButton.rec.width / 2)) - playButtonSize.x / 2 , (playButton.rec.y + (playButton.rec.height / 2)) - playButtonSize.y / 2 }), 54, 0, RAYWHITE);
		DrawTextEx(mainFont, "Quit", Vector2({ (quitButton.rec.x + (quitButton.rec.width / 2)) - quitButtonSize.x / 2, (quitButton.rec.y + (quitButton.rec.height / 2)) - quitButtonSize.y / 2 }), 54, 0, RAYWHITE);

		EndDrawing();
	}

	return false;
}