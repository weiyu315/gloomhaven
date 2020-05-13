#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

class card
{
public:
	int amount;
	vector<vector<string> > cardData;
};
class character
{
public:
	character();
	void getData(string, vector<character>);
	card Card;
private:
	string name;
	int hp;
	int cardNumber;
	int attack;
	int shield;
};

character::character()
{
	name.clear();
	hp = 0;
	cardNumber = 0;
	attack = 0;
	shield = 0;
}
void character::getData(string fileName, vector<character> cha)
{
	ifstream characterData(fileName);
	int number;
	string data;
	characterData >> number;//Ū�����X������
	for (int i = 0; i < number; i++)//���X������N�]�X��
	{
		character tmp;
		getline(characterData, data);//Ū������򥻸�Ʀ�
		int step = 0;
		for (int j = 0; j < data.size(); j++)//�N�C�Ө��⪺�򥻸��(name,hp,��P��)�ǤJclass�̭�
		{
			if (data[j] == ' ')
			{
				step++;
				continue;
			}
			if (step == 0)
			{
				tmp.name += data[j];
			}
			else if (step == 1)
			{
				tmp.hp = tmp.hp * 10 + data[j] - '0';
			}
			else if (step == 2)
			{
				tmp.cardNumber = tmp.cardNumber * 10 + data[j] - '0';
			}
		}
		cha.push_back(tmp);
		characterData >> Card.amount;
		Card.cardData.resize(Card.amount);
		for (int i = 0; i < Card.amount; i++)
		{
			string tmp;
			getline(characterData, tmp);
			Card.cardData[i].push_back(tmp);
		}
	}
}