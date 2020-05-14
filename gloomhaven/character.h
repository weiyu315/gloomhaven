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
	void setName(string newName);
	void setHp(int newHp);
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
	void set_initialCardAmount(int amount);
	int get_initialCardAmount() const;
	void getData(string fileName);
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
	creature::setName(newName);
	creature::setHp(newHp);
	initialCardAmount = newInitialCardAmount;
}
void character::set_initialCardAmount(int amount)
{
	initialCardAmount = amount;
}
int character::get_initialCardAmount() const
{
	return initialCardAmount;
}
void character::getData(string fileName)
{//讀取檔案存入class
	ifstream inFile(fileName, ios::in);
	int characterAmount;
	cin >> characterAmount;//有幾隻角色
	vector<character> cha;
	for (int times = 0; times < characterAmount; times++)
	{
		character tmp;
		string characterInfo;
		getline(inFile, characterInfo);
		string nameTmp = nullptr;
		int hpTmp = 0, initialCardAmountTmp = 0;
		int step = 0;
		for (int i = 0; i < characterInfo.size(); i++)
		{//得到角色資料
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
	}
	inFile.close();
}