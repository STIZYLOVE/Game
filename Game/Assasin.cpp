#include "Assasin.h"
#include <iostream>
#include <fstream>

using namespace std;

Assasin::Assasin()
{
	name = "ассасин";
	maxHealth = 20;
	health = 20;
	damage = 15;
}

Assasin::Assasin(std::string name, unsigned int health, float damage)
{
	cout << "Кастомный конструктор ассасина" << endl;
	this->name = name;
	this->health = health;
	this->damage = damage;
}

void Assasin::GetInfo()
{
	Npc::GetInfo();
	cout << "Коэффициент уклонения - " << evasionFactor << endl;
}

void Assasin::Create()
{
	cout << "Вы создали ассасина" << endl;
	cout << "Введите имя персонажа\t";
	cin >> name;
	cout << endl;
	GetInfo();
	cout << endl;
}

Assasin Assasin::operator + (const Assasin& assasin) const
{
	return Assasin(
		this->name,
		(this->health + assasin.health),
		(this->damage + assasin.damage)
	);
}

Assasin::~Assasin()
{
	cout << name << " испустил дух" << endl;
}

