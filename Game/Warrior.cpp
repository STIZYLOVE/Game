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
}

Warrior::Warrior(std::string name, unsigned int health, float damage)
{
	cout << "кастомный конструктор война" << endl;
	this->name = name;
	this->health = health;
	this->damage = damage;
}

void Warrior::GetWeapons()
{
	cout << name << " взял в руки " << weapons[lvl - 1];
}

void Warrior::GetInfo()
{
	Npc::GetInfo();
	cout << "Сила - " << strenght << endl;
	cout << "Доступное оружие - ";
	for (int i = 0; i < lvl; i++)
	{
		cout << weapons[i] << endl;
	}
}

void Warrior::Create()
{
	cout << "Вы создали война" << endl;
	cout << "Введите имя персонажа\t";
	cin >> name;
	cout << endl;
	GetInfo();
	GetWeapons();
	cout << endl;
	cout << endl;
}

bool Warrior::operator == (const Warrior& warrior) const
{
	return (warrior.damage == this->damage) &&
		(warrior.health == this->health) &&
		(warrior.strenght == this->strenght);
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
