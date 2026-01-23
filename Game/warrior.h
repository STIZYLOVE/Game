#pragma once
#include "NpcClass.h"
#include <string>

class Warrior : public virtual Npc
{
protected:
	unsigned short damageMultiplier;
public:
	Warrior();
	Warrior(string name, int health, float damage);
	~Warrior();

	int CalculateDamage() override;
	void TakeDamage(int damage) override;
	void GetInfo() override;
	void Create() override;

	void UpgradePassive() override;

	bool operator == (const Warrior& warrior) const;

	Warrior& operator = (const Npc& npc);
};