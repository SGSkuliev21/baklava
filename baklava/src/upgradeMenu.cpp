#include "raylib.h"
#include "../headerFiles/tower.h"
#include "../headerFiles/upgradeMenu.h"

void drawUpgradeMenu(Button &upgradeDamageButton, Button &upgradeRegenButton, Button &upgradeMultiKillButton)
{
	DrawRectangleRec(Rectangle({ 0.0f, 110.0f, 250.0f, 100.0f }), CLITERAL(Color){0,0,0, 45});

	DrawRectangleRec(upgradeDamageButton.buttonPosition, RED);
	DrawText("Upgrade Damage", 20, 118, 20, BLACK);
	DrawRectangleRec(upgradeRegenButton.buttonPosition, GREEN);
	DrawText("Upgrade Regen", 20, 148, 20, BLACK);
	DrawRectangleRec(upgradeMultiKillButton.buttonPosition, YELLOW);
	DrawText("Upgrade Multi Kill", 20, 178, 20, BLACK);
}

void upgradeRegen(TowerStats &towerStats, int &gold, Button &upgradeRegenButton)
{
	if (CheckCollisionPointRec(GetMousePosition(), upgradeRegenButton.buttonPosition) && IsMouseButtonPressed(0))
	{

		if (gold >= 20)
		{
			towerStats.towerRegen += 0.005;
			gold -= 20;
		}
	}


	if (CheckCollisionPointRec(GetMousePosition(), upgradeRegenButton.buttonPosition))
	{
		DrawRectangleRec(upgradeRegenButton.buttonPosition, DARKGREEN);
		DrawText("Upgrade Regen", 20, 148, 20, BLACK);
	}
}

void upgradeDamage(TowerStats& towerStats, int& gold, Button& upgradeDamageButton)
{
	if (CheckCollisionPointRec(GetMousePosition(), upgradeDamageButton.buttonPosition) && IsMouseButtonPressed(0))
	{

		if (gold >= 15)
		{
			towerStats.attackPower += 5;
			gold -= 15;
		}
	}

	if (CheckCollisionPointRec(GetMousePosition(), upgradeDamageButton.buttonPosition))
	{
		DrawRectangleRec(upgradeDamageButton.buttonPosition, CLITERAL(Color){139, 0, 0, 255});
		DrawText("Upgrade Damage", 20, 118, 20, BLACK);
	}
}

void upgradeMultiKill(TowerStats& towerStats, int& gold, Button& upgradeMultiKillButton)
{
	if (CheckCollisionPointRec(GetMousePosition(), upgradeMultiKillButton.buttonPosition) && IsMouseButtonPressed(0) && towerStats.multiKill < 4)
	{
		if (gold >= 30)
		{
			towerStats.multiKill++;
			gold -= 30;
		}

	}
	if (CheckCollisionPointRec(GetMousePosition(), upgradeMultiKillButton.buttonPosition))
	{
		if (towerStats.multiKill == 3)
		{
			DrawText("You can upgrade multi kill only 3 times", 5, 210, 20, BLACK);
		}
		DrawRectangleRec(upgradeMultiKillButton.buttonPosition, CLITERAL(Color){139, 128, 0, 255});
		DrawText("Upgrade Multi Kill", 20, 178, 20, BLACK);
	}

}