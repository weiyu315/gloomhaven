#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"card.h"

using namespace std;

class creature :public card
{
public:
	creature();
	creature(string newName, int newHp);
	void setName(string newName);
	void setHp(int newHp);
	string getName();
	int getHp();
private:
	string name;
	int hp;
	vector<card> cardDatabase;
};
class character :public creature
{
public:
	character();
	character(string newName, int newHp, int newInitialCardAmount);
	//void set_AllData(string newName, int newHp, int newInitialCardAmount);
	void set_initialCardAmount(int amount);
	void setCardDatabase(int cardNumber, int cardDex, vector<string> upperSkill, vector<string> lowerSkill);
	int get_initialCardAmount() const;
	//getCardDatabase
	void setFileData_intoClass(string, vector<character>);//讀取檔案存入class
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
void creature::setName(string newName)
{
	name = newName;
}
void creature::setHp(int newHp)
{
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
	setName(newName);
	setHp(newHp);
	initialCardAmount = newInitialCardAmount;
}
//void character::set_AllData(string newName, int newHp, int newInitialCardAmount)
//{
//	setName(newName);
//	setHp(newHp);
//	set_initialCardAmount(newInitialCardAmount);
//}
void character::set_initialCardAmount(int amount)
{
	initialCardAmount = amount;
}
void character::setCardDatabase(int cardNumber, int cardDex, vector<string> upperSkill, vector<string> lowerSkill)
{
	setCardNumber(cardNumber);
	setCardDex(cardDex);
	setUpperSkill(upperSkill);
	setLowerSkill(lowerSkill);
}
int character::get_initialCardAmount() const
{
	return initialCardAmount;
}
void character::setFileData_intoClass(string fileName, vector<character> cha)
{//讀取檔案存入class
	ifstream inFile(fileName, ios::in);
	int characterAmount;
	cin >> characterAmount;//有幾隻角色
	for (int character_number = 0; character_number < characterAmount; character_number++)
	{
		character tmp;
		string characterInfo;
		getline(inFile, characterInfo);
		string nameTmp;
		nameTmp.clear();
		int hpTmp = 0, initialCardAmountTmp = 0;
		int step = 0;
		for (int i = 0; i < characterInfo.size(); i++)
		{//tmp(character)得到角色資料
			if (characterInfo[i] == ' ')
			{
				step++;
				continue;
			}
			if (step == 0)
			{
				nameTmp += characterInfo[i];
			}
			else if (step == 1)
			{
				hpTmp = hpTmp * 10 + characterInfo[i];
			}
			else if (step == 2)
			{
				initialCardAmountTmp = initialCardAmountTmp * 10 + characterInfo[i];
			}
			else
			{
				break;
			}
		}
		tmp.setName(nameTmp);
		tmp.setHp(hpTmp);
		tmp.set_initialCardAmount(initialCardAmountTmp);
		cha.push_back(tmp);//透過tmp存入class
		//卡片部分
		int cardAmount = 0;
		cin >> cardAmount;
		int newNumber, newDex;
		for (int cardNumber = 0; cardNumber < cardAmount; cardNumber++)
		{
			inFile >> newNumber >> newDex;

		}
	}
	inFile.close();
}