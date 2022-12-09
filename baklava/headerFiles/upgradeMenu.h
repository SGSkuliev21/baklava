#pragma once

struct Button
{
	Rectangle buttonPosition;
};

void drawUpgradeMenu(Button& upgradeDamageButton, Button& upgradeRegenButton, Button& upgradeMultyKillButton);
void upgradeRegen(TowerStats& towerStats, int& gold, Button& upgradeRegenButton);
void upgradeDamage(TowerStats& towerStats, int& gold, Button& upgradeDamageButton);
void upgradeMultyKill(TowerStats& towerStats, int& gold, Button& upgradeMultyKillButton);