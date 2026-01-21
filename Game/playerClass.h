#pragma once
using namespace std;
#include <fstream> 
#include <iostream>
#include "NpcClass.h"

class Player
{
private:
	unique_ptr<Npc> currentCharacter{ nullptr };
public:
	void Create(unique_ptr<Npc> player)
	{
		currentCharacter = move(player);
		currentCharacter->Create();
	}
	void Create()
	{
		if (currentCharacter != nullptr)
			currentCharacter->Create();
	}
	Npc* GetCharacter() {
		return currentCharacter.get();
	}
};