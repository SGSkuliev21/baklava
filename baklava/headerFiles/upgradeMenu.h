#pragma once
#include "../headerFiles/buttonHandler.h"

void openUpgradeMenu(Button& menuButton, Rectangle& menu, bool oc);

/// Draw upgrade menu
/// 
/// Displayes the upgrade menu with the upgrade buttons inside.
/// @param upgradeDamageButton custom struct that contains butttonPosition for the upgrade damage button
/// @param upgradeRegenButton custom struct that contains butttonPosition for the upgrade regen button
/// @param upgradeMultiKillButton custom struct that contains butttonPosition for the upgrade multi kill button
void drawUpgradeMenu(Button& upgradeDamageButton, Button& upgradeRegenButton, Button& upgradeMultiKillButton);

/// When right mouse button is pressed upgrade regen
/// 
/// When the right mouse button is pressed and the player has 20 gold the towerRegen is incremented by 0.005 every time and the gold is decremented by 20.
/// @param towerStats the stats of the tower
/// @param gold the avalible gold
/// @param upgradeDamageButton custom struct with the information for the upgrade regen button
/// @see TowerStats
/// @see Button
void upgradeRegen(TowerStats& towerStats, int& gold, Button& upgradeRegenButton);

/// When right mouse button is pressed upgrade damage
/// 
/// When the right mouse button is pressed and the player has 15 gold the towerAttackPower is incremented by 5 every time and the gold is decremented by 15.
/// @param towerStats the stats of the tower
/// @param gold the avalible gold
/// @param upgradeRegenButton custom struct with the information for the damage regen button
/// @see TowerStats
/// @see Button
void upgradeDamage(TowerStats& towerStats, int& gold, Button& upgradeDamageButton);

/// When right mouse button is pressed upgrade multi kill
/// 
/// When the right mouse button is pressed, the player has 35 gold and multiKill is less than 3 the multi is incremented by 1 every time and the gold is decremented by 35.
/// @param towerStats the stats of the tower
/// @param gold the avalible gold
/// @param upgradeMultiKillButton custom struct with the information for the damage regen button
/// @see TowerStats
/// @see Button
void upgradeMultiKill(TowerStats& towerStats, int& gold, Button& upgradeMultiKillButton);