#pragma once
#include "buttonHandler.h"

/// Special button that stores upgrade specific data
struct UpgradeButton
{
	Button button;
	int timesBought;
	int price;
};

/// Opens up a sidebar with upgrades
/// 
/// This function opens up a sidebar with all available upgrades and closes it at the press of a button
/// @param upgrade1 dmg up button
/// @param upgrade2 regen up button
/// @param upgrade3 multikill up button
/// @param menuButton the button that opens and closes the menu
/// @param menu the menu the buttons are on
/// @param oc a parameter that decides whether the menu should be open or not
/// @see Button
void openUpgradeMenu(Button& upgrade1, Button& upgrade2, Button& upgrade3, Button& menuButton, Rectangle& menu, bool oc);

/// Upgrade regen
/// 
/// When the player has 20 gold the towerRegen is incremented by 0.005 every time and the gold is decremented by 20.
/// @param towerStats the stats of the tower
/// @param gold the avalible gold
/// @param upgradeDamageButton custom struct with the information for the upgrade regen button
/// @see TowerStats
/// @see UpgradeButton
void upgradeRegen(TowerStats& towerStats, int& gold, UpgradeButton& regen);

/// Upgrade damage
/// 
/// When the player has 15 gold the towerAttackPower is incremented by 5 every time and the gold is decremented by 15.
/// @param towerStats the stats of the tower
/// @param gold the avalible gold
/// @param upgradeRegenButton custom struct with the information for the damage regen button
/// @see TowerStats
/// @see UpgradeButton
void upgradeDamage(TowerStats& towerStats, int& gold, UpgradeButton& damage);

/// Upgrade multi kill
/// 
/// When the player has 35 gold and multiKill is less than 3 the multi is incremented by 1 every time and the gold is decremented by 35.
/// @param towerStats the stats of the tower
/// @param gold the avalible gold
/// @param upgradeMultiKillButton custom struct with the information for the damage regen button
/// @see TowerStats
/// @see UpgradeButton
void upgradeMultiKill(TowerStats& towerStats, int& gold, UpgradeButton& multiKill);