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

void Enemy::GetInfo() {
	cout << endl;
	cout << "На вас напал " << name << endl;
	if (health >= 0 && damage < 0) {
		cout << "Здоровье - " << health << endl;
	}
	if (health < 0 && damage >= 0) {
		cout << "урон - " << damage << endl;
	}
	if (health >= 0 && damage >= 0) {
		cout << "Здоровье - " << health << endl;
		cout << "урон - " << damage << endl;
	}
}