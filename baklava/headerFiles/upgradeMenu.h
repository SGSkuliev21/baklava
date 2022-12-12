#pragma once
#include "buttonHandler.h"

struct UpgradeButton
{
	Button button;
	int timesBought;
	int price;
};

void openUpgradeMenu(Button& upgrade1, Button& upgrade2, Button& upgrade3, Button& menuButton, Rectangle& menu, bool oc);

/// When right mouse button is pressed upgrade regen
/// 
/// When the right mouse button is pressed and the player has 20 gold the towerRegen is incremented by 0.005 every time and the gold is decremented by 20.
/// @param towerStats the stats of the tower
/// @param gold the avalible gold
/// @param upgradeDamageButton custom struct with the information for the upgrade regen button
/// @see TowerStats
/// @see Button
void upgradeRegen(TowerStats& towerStats, int& gold, UpgradeButton& regen);

/// When right mouse button is pressed upgrade damage
/// 
/// When the right mouse button is pressed and the player has 15 gold the towerAttackPower is incremented by 5 every time and the gold is decremented by 15.
/// @param towerStats the stats of the tower
/// @param gold the avalible gold
/// @param upgradeRegenButton custom struct with the information for the damage regen button
/// @see TowerStats
/// @see Button
void upgradeDamage(TowerStats& towerStats, int& gold, UpgradeButton& damage);

/// When right mouse button is pressed upgrade multi kill
/// 
/// When the right mouse button is pressed, the player has 35 gold and multiKill is less than 3 the multi is incremented by 1 every time and the gold is decremented by 35.
/// @param towerStats the stats of the tower
/// @param gold the avalible gold
/// @param upgradeMultiKillButton custom struct with the information for the damage regen button
/// @see TowerStats
/// @see Button
void upgradeMultiKill(TowerStats& towerStats, int& gold, UpgradeButton& multiKill);