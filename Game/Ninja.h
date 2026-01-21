#pragma once
#include "NpcClass.h"
#include "Assasin.h"
#include "Warrior.h"
#include <string>

class Ninja : public Warrior, public Assasin
{
public:
	Ninja();
	void GetInfo() override;
	void Create() override;
};