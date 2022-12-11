#include "raylib.h"
#include "../headerFiles/mainMenu.h"

//Setting button state depending on mouse actions
void setButtonState(Button& button)
{
	button.state = 0;
	if (CheckCollisionPointRec(GetMousePosition(), button.rect))
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			button.state = 2;
		}
		else
		{
			button.state = 1;
		}

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			button.state = 3;
		}
	}
}

bool changeButtonByState(Button& button)
{
	if (button.state == 3)
	{
		return true;
	}
	else
	{
		if (button.state == 0)
		{
			if (button.rect.width > 309)
			{
				button.rect.width -= 6.0f;
				button.rect.height -= 3.0f;
				button.rect.y += 1.5f;
			}
		}
		else if (button.state == 1 || button.state == 2)
		{
			if (button.rect.width < 319)
			{
				button.rect.width += 6.0f;
				button.rect.height += 3.0f;
				button.rect.y -= 1.5f;
			}
		}
		DrawRectangleRec(button.rect, button.color);
		DrawRectangleLinesEx(button.rect, 3, RAYWHITE);
	}
	if (button.state == 2)
	{
		DrawRectangleRec(button.rect, button.hoverColor);
		DrawRectangleLinesEx(button.rect, 3, LIGHTGRAY);
	}

	return false;
}

bool mainMenuLoop()
{
	Font mainFont = LoadFontEx("assets/fonts/MainFont.ttf", 54, NULL, 0);
	SetTextureFilter(mainFont.texture, TEXTURE_FILTER_BILINEAR);
	//Declaring the play button
	Button playButton;
	playButton.rect = { -6, 251, 319, 109 };
	playButton.state = 0;
	playButton.color = CLITERAL(Color){ 194, 51, 51, 255 };
	playButton.hoverColor = CLITERAL(Color) { 154, 11, 11, 255 };

	//Declaring the quit button
	Button quitButton;
	quitButton.rect = { -6, 421, 319, 109 };
	quitButton.state = 0;
	quitButton.color = CLITERAL(Color) { 158, 47, 197, 255 };
	quitButton.hoverColor = CLITERAL(Color) { 138, 17, 167, 255 };


	while (!WindowShouldClose())
	{
		BeginDrawing();

		//Clearing image
		ClearBackground(RAYWHITE);

		//Drawing the background gradient
		DrawRectangleGradientH(0, 0, 1280, 720, CLITERAL(Color){2, 171, 58, 255}, CLITERAL(Color){1, 97, 33, 255});
		DrawRectangleGradientV(0, 0, 1280, 720, CLITERAL(Color){ 2, 171, 58, 123 }, CLITERAL(Color){ 1, 97, 33, 123 });

		//Drawing title
		DrawTextEx(mainFont, "Baklava TD", Vector2({ 640 - MeasureTextEx(mainFont, "Baklava TD", 54, 0).x / 2, 100}), 54, 0, RAYWHITE);

		setButtonState(playButton);
		setButtonState(quitButton);

		if (changeButtonByState(playButton)) return true;
		if (changeButtonByState(quitButton)) return false;

		DrawTextEx(mainFont, "Play", Vector2({ playButton.rect.x + (playButton.rect.width / 12), playButton.rect.y + (playButton.rect.height / 4) }), 54, 0, RAYWHITE);
		DrawTextEx(mainFont, "Quit", Vector2({ quitButton.rect.x + (quitButton.rect.width / 15), quitButton.rect.y + (quitButton.rect.height / 4) }), 54, 0, RAYWHITE);

		EndDrawing();
	}

	UnloadFont(mainFont);

	CloseWindow();

	return false;
}