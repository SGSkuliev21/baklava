#include "raylib.h"
#include "../headerFiles/mainMenu.h"

//Setting button state depending on mouse actions
void setButtonState(Button& button)
{
	button.state = 0;
	if (CheckCollisionPointRec(GetMousePosition(), button.rec))
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
			if (button.rec.width > 309)
			{
				button.rec.width -= 120.0f * GetFrameTime();
				button.rec.height -= 60.0f * GetFrameTime();
				button.rec.y += 30.0f * GetFrameTime();
			}
		}
		else if (button.state == 1 || button.state == 2)
		{
			if (button.rec.width < 319)
			{
				button.rec.width += 120.0f * GetFrameTime();
				button.rec.height += 60.0f * GetFrameTime();
				button.rec.y -= 30.0f * GetFrameTime();
			}
		}
		DrawRectangleRec(button.rec, button.color);
		DrawRectangleLinesEx(button.rec, 3, RAYWHITE);
	}
	if (button.state == 2)
	{
		DrawRectangleRec(button.rec, button.hoverColor);
		DrawRectangleLinesEx(button.rec, 3, LIGHTGRAY);
	}

	return false;
}

bool fadeToGame()
{
	Rectangle fadeRec1 = { -1920, 0, 1920, 190 };
	Rectangle fadeRec2 = { 1280, 190, 1920, 190 };
	Rectangle fadeRec3 = { -1920, 370, 1920, 190 };
	Rectangle fadeRec4 = { 1280, 530, 1920, 190 };

	bool closeFlag = false;

	while (fadeRec4.x > -720 && !WindowShouldClose())
	{
		BeginDrawing();

		fadeRec1.x += 2220.0f * GetFrameTime();
		DrawRectangleRec(fadeRec1, BLACK);

		fadeRec2.x -= 2220.0f * GetFrameTime();
		DrawRectangleRec(fadeRec2, BLACK);

		fadeRec3.x += 2220.0f * GetFrameTime();
		DrawRectangleRec(fadeRec3, BLACK);

		fadeRec4.x -= 2220.0f * GetFrameTime();
		DrawRectangleRec(fadeRec4, BLACK);
		
		EndDrawing();
	}
	
	if (fadeRec4.x <= -720) return true;
	else return false;
}

bool mainMenuLoop()
{
	Font mainFont = LoadFontEx("assets/fonts/MainFont.ttf", 54, NULL, 0);
	SetTextureFilter(mainFont.texture, TEXTURE_FILTER_BILINEAR);
	//Declaring the play button
	Button playButton;
	playButton.rec = { -6, 251, 319, 109 };
	playButton.state = 0;
	playButton.color = CLITERAL(Color){ 194, 51, 51, 255 };
	playButton.hoverColor = CLITERAL(Color) { 154, 11, 11, 255 };

	//Declaring the quit button
	Button quitButton;
	quitButton.rec = { -6, 421, 319, 109 };
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

		if (changeButtonByState(playButton))
		{
			if (fadeToGame()) return true;
			else return false;
		}
		if (changeButtonByState(quitButton)) return false;

		DrawTextEx(mainFont, "Play", Vector2({ playButton.rec.x + (playButton.rec.width / 12), playButton.rec.y + (playButton.rec.height / 4) }), 54, 0, RAYWHITE);
		DrawTextEx(mainFont, "Quit", Vector2({ quitButton.rec.x + (quitButton.rec.width / 15), quitButton.rec.y + (quitButton.rec.height / 4) }), 54, 0, RAYWHITE);

		EndDrawing();
	}

	UnloadFont(mainFont);

	CloseWindow();

	return false;
}