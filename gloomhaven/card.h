#pragma once
#include<iostream>
#include<vector>
#include<string>

using namespace std;

//struct cardAction
//{
//	string action;
//	int value;
//};
class cardValue
{
public:
	cardValue();
	cardValue(int newAttack, int newShield, int newMove, int newRange, int newHeal);
	int attack;
	int shield;
	int move;
	int range;
	int heal;
};
class card
{
public:
	card();
	card(int newCardNumber, int newCardDex, vector<cardValue> skill[2]);
	void setCardNumber(int);
	void setCardDex(int);
	void setSkill(card cardTmp, string skill_name, int skill_value ,bool upper);
	int getCardNumber() const;
	int getCardDex() const;
private:
	int cardNumber;
	int cardDex;
	vector<cardValue> skill[2];//0為上半部分 1為下半部分
	//vector<cardAction> upperAction;
	//vector<cardAction> lowerAction;
};

cardValue::cardValue()
{
	attack = 0;
	shield = 0;
	move = 0;
	range = 0;
	heal = 0;
}
cardValue::cardValue(int newA, int newS, int newM, int newR, int newH)
{
	attack = newA;
	shield = newS;
	move = newM;
	range = newR;
	heal = newH;
}

card::card()
{
	cardNumber = 0;
	cardDex = 0;
	skill[0].clear();
	skill[1].clear();
}
card::card(int newCardNumber, int newCardDex, vector<cardValue> newSkill[2])
{
	cardNumber = newCardNumber;
	cardDex = newCardDex;
	skill[0].assign(newSkill[0].begin(), newSkill[0].end());
	skill[1].assign(newSkill[1].begin(), newSkill[1].end());
}
void card::setCardNumber(int newCardNumber)
{
	cardNumber = newCardNumber;
}
void card::setCardDex(int newCardDex)
{
	cardDex = newCardDex;
}
void card::setSkill(card cardTmp, string skill_name, int skill_value, bool upper)
{
	cardValue tmp;
	switch (skill_name[0])
	{
	case'a':
		tmp.attack= skill_value;
		break;
	case's':
		tmp.shield = skill_value;
		break;
	case'm':
		tmp.move = skill_value;
		break;
	case'r':
		tmp.range = skill_value;
		break;
	case'h':
		tmp.heal = skill_value;
		break;
	default:
		break;
	}
	if (upper)
	{
		cardTmp.skill[0].push_back(tmp);
	}
	else
	{
		cardTmp.skill[1].push_back(tmp);
	}
}
int card::getCardNumber() const
{
	return cardNumber;
}
int card::getCardDex() const
{
	return cardDex;
}