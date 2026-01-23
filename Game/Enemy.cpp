#pragma once
#include "Enemy.h"
#include <string>

Enemy::Enemy(std::string name) {
	this->name = name;
	health = 10;
	damage = 5;
}
Enemy::Enemy(string name, int health) : Enemy(name) {
	this->health = health;
}
Enemy::Enemy(string name, int health, int damage) : Enemy(name, health) {
	this->damage = damage;
}

void Enemy::TakeDamage(int damage)
{
	Npc::TakeDamage(damage);
}

void Enemy::GetInfo() {
	cout << endl;
	cout << "На вас напал - " << name << endl;
	if(health < 0)
		cout << "Здоровье - 0" << endl;
	else
		cout << "Здоровье - " << health << endl;
	cout << "Урон - " << damage << endl;
}