#include "raylib.h"
#include "../headerFiles/tower.h"
#include "../headerFiles/upgradeMenu.h"
#include "../headerFiles/mainMenu.h"

void drawUpgradeMenu(Button &upgradeDamageButton, Button &upgradeRegenButton, Button &upgradeMultiKillButton)
{
	DrawRectangleRec(Rectangle({ 0.0f, 110.0f, 250.0f, 100.0f }), CLITERAL(Color){0,0,0, 45});

	DrawRectangleRec(upgradeDamageButton.rect, CLITERAL(Color){189, 0 , 0, 255});
	DrawText("Upgrade Damage", 20, 118, 20, BLACK);
	DrawRectangleRec(upgradeRegenButton.rect, CLITERAL(Color){0, 155, 0, 255});
	DrawText("Upgrade Regen", 20, 148, 20, BLACK);
	DrawRectangleRec(upgradeMultiKillButton.rect, CLITERAL(Color){204, 204, 0, 255});
	DrawText("Upgrade Multi Kill", 20, 178, 20, BLACK);
}

void upgradeRegen(TowerStats &towerStats, int &gold, Button &upgradeRegenButton)
{
	if (CheckCollisionPointRec(GetMousePosition(), upgradeRegenButton.rect) && IsMouseButtonPressed(0))
	{

		if (gold >= 20)
		{
			towerStats.towerRegen += 0.005;
			gold -= 20;
		}
	}


	if (CheckCollisionPointRec(GetMousePosition(), upgradeRegenButton.rect))
	{
		DrawRectangleRec(upgradeRegenButton.rect, DARKGREEN);
		DrawText("Upgrade Regen", 20, 148, 20, BLACK);
	}
}

void upgradeDamage(TowerStats& towerStats, int& gold, Button& upgradeDamageButton)
{
	if (CheckCollisionPointRec(GetMousePosition(), upgradeDamageButton.rect) && IsMouseButtonPressed(0))
	{

		if (gold >= 15)
		{
			towerStats.attackPower += 5;
			gold -= 15;
		}
	}

	if (CheckCollisionPointRec(GetMousePosition(), upgradeDamageButton.rect))
	{
		DrawRectangleRec(upgradeDamageButton.rect, CLITERAL(Color){139, 0, 0, 255});
		DrawText("Upgrade Damage", 20, 118, 20, BLACK);
	}
}

void upgradeMultiKill(TowerStats& towerStats, int& gold, Button& upgradeMultiKillButton)
{
	if (CheckCollisionPointRec(GetMousePosition(), upgradeMultiKillButton.rect) && IsMouseButtonPressed(0) && towerStats.multiKill < 3)
	{
		if (gold >= 30)
		{
			towerStats.multiKill++;
			gold -= 30;
		}

	}
	if (CheckCollisionPointRec(GetMousePosition(), upgradeMultiKillButton.rect))
	{
		if (towerStats.multiKill == 3)
		{
			DrawText("You can only upgrade multi kill 3 times", 5, 210, 20, BLACK);
		}
		DrawRectangleRec(upgradeMultiKillButton.rect, CLITERAL(Color){139, 128, 0, 255});
		DrawText("Upgrade Multi Kill", 20, 178, 20, BLACK);
	}

}