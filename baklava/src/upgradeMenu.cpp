#include "raylib.h"
#include "../headerFiles/upgradeMenu.h"

void drawUpgradeMenu()
{
	Button upgradeDamageButton; 
	Button upgradeRegenButton;
	Button upgradeMultyKillButton;
	upgradeDamageButton.buttonPosition = { 18.0f, 115.0f, 200.0f, 25.0f };
	upgradeRegenButton.buttonPosition = { 18.0f, 145.0f, 200.0f, 25.0f };
	upgradeMultyKillButton.buttonPosition = { 18.0f, 175.0f, 200.0f, 25.0f };

	DrawRectangleRec(Rectangle({ 0.0f, 110.0f, 250.0f, 100.0f }), CLITERAL(Color){0,0,0, 45});

	DrawRectangleRec(upgradeDamageButton.buttonPosition, RED);
	DrawText("Upgrade Damage", 20, 118, 20, BLACK);
	DrawRectangleRec(upgradeRegenButton.buttonPosition, GREEN);
	DrawText("Upgrade Regen", 20, 148, 20, BLACK);
	DrawRectangleRec(upgradeMultyKillButton.buttonPosition, YELLOW);
	DrawText("Upgrade Multy Kill", 20, 178, 20, BLACK);
}