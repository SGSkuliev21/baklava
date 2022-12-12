#include "raylib.h"
#include "../headerFiles/tower.h"
#include "../headerFiles/upgradeMenu.h"
#include "../headerFiles/buttonHandler.h"

void openUpgradeMenu(Button& upgrade1, Button& upgrade2, Button& upgrade3, Button& menuButton, Rectangle& menu, bool oc)
{
	if (oc)
	{
		if (menu.x <= 0)
		{
			upgrade1.rec.x += 360.0f * GetFrameTime();
			upgrade2.rec.x += 360.0f * GetFrameTime();
			upgrade3.rec.x += 360.0f * GetFrameTime();
			menuButton.rec.x += 360.0f * GetFrameTime();
			menu.x += 360.0f * GetFrameTime();
		}
	}
	else
	{
		if (menu.x >= -324)
		{
			upgrade1.rec.x -= 360.0f * GetFrameTime();
			upgrade2.rec.x -= 360.0f * GetFrameTime();
			upgrade3.rec.x -= 360.0f * GetFrameTime();
			menuButton.rec.x -= 360.0f * GetFrameTime();
			menu.x -= 360.0f * GetFrameTime();
		}
	}
}

void upgradeRegen(TowerStats &towerStats, int &gold, UpgradeButton &regen)
{
	if (gold >= regen.price)
	{
		regen.timesBought++;
		towerStats.towerRegen += 0.005;
		gold -= regen.price;
	}
}

void upgradeDamage(TowerStats& towerStats, int& gold, UpgradeButton& damage)
{
	if (gold >= damage.price)
	{
		damage.timesBought++;
		towerStats.attackPower += 5;
		gold -= damage.price;
	}
}

void upgradeMultiKill(TowerStats& towerStats, int& gold, UpgradeButton& multiKill)
{
	if (multiKill.timesBought == 3)
	{
		DrawText("You can only upgrade multi kill 3 times", 5, 210, 20, BLACK);
	}
	else if (gold >= multiKill.price)
	{
		multiKill.timesBought;
		towerStats.multiKill++;
		gold -= multiKill.price;
	}
}