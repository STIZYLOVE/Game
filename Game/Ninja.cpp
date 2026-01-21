#include "Ninja.h"
#include <iostream>
#include <fstream>

using namespace std;

Ninja::Ninja()
{
	name = "нинзя";
	maxHealth = 25;
	health = 25;
	damage = 12;
	strenght = 27;
}

void Ninja::GetInfo()
{
	Warrior::GetInfo();
}

void Ninja::Create()
{
	cout << "Вы создали нинзя" << endl;
	cout << "Введите имя персонажа\t";
	cin >> name;
	cout << endl;
	GetInfo();
	GetWeapons();
	cout << endl;
}