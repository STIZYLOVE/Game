#pragma once
#include "NpcClass.h"
#include <string>

class Assasin : public virtual Npc
{
protected:
	unsigned short doubleDamageChance;
public:
	Assasin();
	Assasin(std::string name, int health, float damage);
	~Assasin();

	void TakeDamage(int damage) override;
	int CalculateDamage() override;
	void GetInfo() override;
	void Create() override;

	Assasin operator + (const Assasin& assasin) const;

};