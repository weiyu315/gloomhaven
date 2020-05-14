#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

class creature
{
public:
	creature();
	creature(string newName, int newHp);
	string getName();
	int getHp();
private:
	string name;
	int hp;
};
class character :public creature
{
public:
	character();
	character(string newName, int newHp, int newInitialCardAmount);
	int get_initialCardAmount() const;
private:
	int initialCardAmount;
};
creature::creature()
{
	name.clear();
	hp = 0;
}
creature::creature(string newName, int newHp)
{
	name = newName;
	hp = newHp;
}
string creature::getName()
{
	return name;
}
int creature::getHp()
{
	return hp;
}
character::character()
{
	initialCardAmount = 0;
}
character::character(string newName, int newHp, int newInitialCardAmount)
{
	creature::creature(newName, newHp);
	initialCardAmount = newInitialCardAmount;
}
int character::get_initialCardAmount() const
{
	return initialCardAmount;
}