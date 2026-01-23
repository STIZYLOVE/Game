#include "Warrior.h"
#include <iostream>
#include <fstream>

using namespace std;

Warrior::Warrior()
{
	name = "воин";
	maxHealth = 35;
	health = 35;
	damage = 10;
	damageMultiplier = 10; // 0 - 100
}

Warrior::Warrior(std::string name, int health, float damage)
{
	cout << "кастомный конструктор война" << endl;
	this->name = name;
	this->health = health;
	this->damage = damage;
}

void Warrior::TakeDamage(int damage)
{
	Npc::TakeDamage(damage);
}

int Warrior::CalculateDamage()
{
	float tempDamage = static_cast<float>(damage) * (1.0f + static_cast<float>(damageMultiplier) / 100.0f);
	return static_cast<int>(tempDamage);
}

void Warrior::GetInfo()
{
	Npc::GetInfo();
	cout << "ћножитель урона(%) - " << damageMultiplier << endl;

}

void Warrior::Create()
{
	cout << "¬ы создали война" << endl;
	cout << "¬ведите им€ персонажа\t";
	cin >> name;
	cout << endl;
	GetInfo();
	cout << endl;
	cout << endl;
}

void Warrior::UpgradePassive()
{
	damageMultiplier += 5;
}

bool Warrior::operator == (const Warrior& warrior) const
{
	return (warrior.damage == this->damage) &&
		(warrior.health == this->health) &&
		(warrior.damageMultiplier == this->damageMultiplier);
}

Warrior& Warrior::operator = (const Npc& npc)
{
	if (this != &npc)
	{
		this->name = npc.GetName();
		this->health = npc.GetHealth();
		this->damage = npc.GetDamage();
		this->lvl = npc.GetLvl();
		return *this;
	}
	return *this;
}

Warrior::~Warrior()
{
	cout << name << " пал смертью храбрых" << endl;
}
