#include "Ninja.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include "consoleManager.h"

using namespace std;

Ninja::Ninja()
{
	name = "нинзя";
	maxHealth = 25;
	health = 25;
	damage = 12;
	evasionFactor = 8; // 1 - 100;
	damageMultiplier = 10;
	doubleDamageChance = 2;
	srand(std::time(0));
}

void Ninja::TakeDamage(int damage)
{
	int random_num = 1 + std::rand() % 100;
	if (random_num <= evasionFactor)
	{
		printSlowly("Вы уклонилось от удара! ", false);
		return;
	}
	Npc::TakeDamage(damage);
}

int Ninja::CalculateDamage()
{
	int random_num = 1 + std::rand() % 100;

	if (random_num <= doubleDamageChance)
	{
		printSlowly("Вы совершили двойной удар!", false);
		return Warrior::CalculateDamage() * 2;
	}

	return Warrior::CalculateDamage();
}

void Ninja::GetInfo()
{
	Warrior::GetInfo();
	cout << "Шанс уклонения(%) - " << evasionFactor << endl;
	cout << "Шанс на вторую атаку(%) - " << doubleDamageChance << endl;
}

void Ninja::Create()
{
	cout << "Вы создали нинзя" << endl;
	cout << "Введите имя персонажа\t";
	cin >> name;
	cout << endl;
	GetInfo();
	cout << endl;
}