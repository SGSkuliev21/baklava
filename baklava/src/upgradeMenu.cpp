#include "raylib.h"
#include "../headerFiles/tower.h"
#include "../headerFiles/upgradeMenu.h"

void drawUpgradeMenu(Button &upgradeDamageButton, Button &upgradeRegenButton, Button &upgradeMultyKillButton)
{
	DrawRectangleRec(Rectangle({ 0.0f, 110.0f, 250.0f, 100.0f }), CLITERAL(Color){0,0,0, 45});

	DrawRectangleRec(upgradeDamageButton.buttonPosition, RED);
	DrawText("Upgrade Damage", 20, 118, 20, BLACK);
	DrawRectangleRec(upgradeRegenButton.buttonPosition, GREEN);
	DrawText("Upgrade Regen", 20, 148, 20, BLACK);
	DrawRectangleRec(upgradeMultyKillButton.buttonPosition, YELLOW);
	DrawText("Upgrade Multy Kill", 20, 178, 20, BLACK);
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

void upgradeMultyKill(TowerStats& towerStats, int& gold, Button& upgradeMultyKillButton)
{
	if (CheckCollisionPointRec(GetMousePosition(), upgradeMultyKillButton.buttonPosition) && IsMouseButtonPressed(0))
	{

		if (gold >= 30)
		{
			towerStats.multyKill++;
			gold -= 30;
		}
	}

	if (CheckCollisionPointRec(GetMousePosition(), upgradeMultyKillButton.buttonPosition))
	{
		DrawRectangleRec(upgradeMultyKillButton.buttonPosition, CLITERAL(Color){139, 128, 0, 255});
		DrawText("Upgrade Multy Kill", 20, 178, 20, BLACK);
	}
}