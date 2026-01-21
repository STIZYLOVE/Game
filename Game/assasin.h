#pragma once
#include "NpcClass.h"
#include <string>

class Assasin : public virtual Npc
{
protected:
	unsigned short evasionFactor = 27;
public:
	Assasin();
	Assasin(std::string name, unsigned int health, float damage);
	~Assasin();

	void GetInfo() override;
	void Create() override;

	Assasin operator + (const Assasin& assasin) const;

};