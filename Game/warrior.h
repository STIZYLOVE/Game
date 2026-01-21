#pragma once
#include "NpcClass.h"
#include <string>

class Warrior : public virtual Npc
{
protected:
	unsigned short strenght{ 31 };
	std::string weapons[4] = { "кастет", "дубинка", "клинок", "меч" };
public:
	Warrior();
	Warrior(std::string name, unsigned int health, float damage);
	~Warrior();

	void GetWeapons();
	void GetInfo() override;
	void Create() override;

	bool operator == (const Warrior& warrior) const;

	Warrior& operator = (const Npc& npc);
};