#include "pch.h"

void openUpgradeMenu(Button& upgrade1, Button& upgrade2, Button& upgrade3, Button& menuButton, Rectangle& menu, bool oc)
{
	if (oc)
	{
		if (menu.x <= 0)
		{
			upgrade1.rec.x += 520.0f * GetFrameTime();
			upgrade2.rec.x += 520.0f * GetFrameTime();
			upgrade3.rec.x += 520.0f * GetFrameTime();
			menuButton.rec.x += 720.0f * GetFrameTime();
			menu.x += 720.0f * GetFrameTime();
		}
	}
	else
	{
		if (menu.x >= -324)
		{
			upgrade1.rec.x -= 520.0f * GetFrameTime();
			upgrade2.rec.x -= 520.0f * GetFrameTime();
			upgrade3.rec.x -= 520.0f * GetFrameTime();
			menuButton.rec.x -= 720.0f * GetFrameTime();
			menu.x -= 720.0f * GetFrameTime();
		}
	}

	if (menu.x < -324)
	{
		menu.x = -324;
		menuButton.rec.x = -4;
		upgrade1.rec.x = -210;
		upgrade2.rec.x = -210;
		upgrade3.rec.x = -210;
	}
	if (menu.x > 0)
	{
		menu.x = 0;
		menuButton.rec.x = 324;
		upgrade1.rec.x = 18;
		upgrade2.rec.x = 18;
		upgrade3.rec.x = 18;
	}
}

void upgradeRegen(TowerStats &towerStats, int &gold, UpgradeButton &regen)
{
	if (gold >= regen.price)
	{
		regen.timesBought++;
		towerStats.towerRegen += 0.005;
		gold -= regen.price;
		regen.price += 5;
	}
}

void upgradeDamage(TowerStats& towerStats, int& gold, UpgradeButton& damage)
{
	if (gold >= damage.price)
	{
		damage.timesBought++;
		towerStats.attackPower += 5;
		gold -= damage.price;
		damage.price += 10;
	}
}

void upgradeMultiKill(TowerStats& towerStats, int& gold, UpgradeButton& multiKill)
{
	if (gold >= multiKill.price)
	{
		multiKill.timesBought++;
		towerStats.multiKill++;
		gold -= multiKill.price;
		multiKill.price += 15;
	}
}