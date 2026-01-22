#pragma once
#include "npcClass.h"

class Enemy : public Npc {
public:
	Enemy(string name);
	Enemy(string name, int health);
	Enemy(string name, int health, int damage);

	void TakeDamage(int damage) override;
	void GetInfo() override;
};