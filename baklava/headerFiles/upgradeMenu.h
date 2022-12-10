#pragma once

struct Button
{
	Rectangle buttonPosition;
};

void drawUpgradeMenu(Button& upgradeDamageButton, Button& upgradeRegenButton, Button& upgradeMultiKillButton);
void upgradeRegen(TowerStats& towerStats, int& gold, Button& upgradeRegenButton);
void upgradeDamage(TowerStats& towerStats, int& gold, Button& upgradeDamageButton);
void upgradeMultiKill(TowerStats& towerStats, int& gold, Button& upgradeMultiKillButton);