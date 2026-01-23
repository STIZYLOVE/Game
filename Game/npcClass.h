#pragma once
using namespace std;
#include <fstream> 
#include <iostream>

class Npc
{
protected:
	string name{ "персонаж" };
	unsigned int maxHealth{ 10 };
	int health{ 10 };
	float damage{ 5 };
	unsigned short lvl{ 1 };
public:
	string GetName() const
	{
		return name;
	}
	int GetHealth() const
	{
		return health;
	}
	float GetDamage() const
	{
		return damage;
	}
	unsigned short GetLvl() const
	{
		return lvl;
	}
	void ChangeMaxHealth(int health)
	{
		maxHealth += health;
	}
	
	virtual void TakeDamage(int damage)
	{
		health -= damage;
		if (health < 0)
		{
			health = 0;
		}
	}

	virtual void AddHealth(int healthAmount)
	{
		health += healthAmount;
		if (health > maxHealth)
		{
			health = maxHealth;
		}
	}

	void NextLevel()
	{
		lvl += 1;
		UpgradePassive();
		cout << "Пассивная способность улучшена.\n" << endl;
	}

	virtual void UpgradePassive() {}
	
	virtual int CalculateDamage() { return 0; };

	virtual void GetInfo()
	{
		cout << "Имя - " << name << endl;
		cout << "Уровень - " << lvl << endl;
		cout << "Максимальное здоровье - " << maxHealth << endl;
		cout << "Здоровье - " << health << endl;
		cout << "Урон - " << damage << endl;
	}
	virtual void Create() {};

	virtual ~Npc() = default;
};
