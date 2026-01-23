#pragma once
#include "NpcClass.h"
#include "Assasin.h"
#include "Warrior.h"
#include <string>

class Ninja : public Warrior, public Assasin
{
protected:
	unsigned short evasionFactor;
public:
	Ninja();
	void TakeDamage(int damage) override;
	int CalculateDamage() override;
	void GetInfo() override;
	void Create() override;
	void UpgradePassive() override;
};