#include "raylib.h"
#include "../headerFiles/buttonHandler.h"

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

bool changeButtonByState(Button& button, float startWidth, bool editWidth)
{
	if (button.state == 3)
	{
		return true;
	}
	else
	{
		if (button.state == 0)
		{
			if (button.rec.width > startWidth)
			{
				button.rec.width -= 120.0f * GetFrameTime();
				button.rec.height -= 60.0f * GetFrameTime();
				button.rec.y += 30.0f * GetFrameTime();
				if (editWidth) button.rec.x += 60.0f * GetFrameTime();
			}
		}
		else if (button.state == 1 || button.state == 2)
		{
			if (button.rec.width < startWidth + 10)
			{
				button.rec.width += 120.0f * GetFrameTime();
				button.rec.height += 60.0f * GetFrameTime();
				button.rec.y -= 30.0f * GetFrameTime();
				if (editWidth) button.rec.x -= 60.0f * GetFrameTime();
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