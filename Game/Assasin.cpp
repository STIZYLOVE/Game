#include "Assasin.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "consoleManager.h"

using namespace std;

Assasin::Assasin()
{
	name = "ассасин";
	maxHealth = 20;
	health = 20;
	damage = 15;
	doubleDamageChance = 10; //1 - 100
}

Assasin::Assasin(std::string name, int health, float damage)
{
	cout << "Кастомный конструктор ассасина" << endl;
	this->name = name;
	this->health = health;
	this->damage = damage;
}

void Assasin::TakeDamage(int damage)
{
	Npc::TakeDamage(damage);
}

int Assasin::CalculateDamage()
{
	int random_num = 1 + std::rand() % 100;

	if (random_num <= doubleDamageChance)
	{
		printSlowly("Вы совершили двойной удар!", false);
		return damage * 2;
	}

	return damage;
}

void Assasin::GetInfo()
{
	Npc::GetInfo();
	cout << "Шанс на вторую атаку(%) - " << doubleDamageChance << endl;
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

