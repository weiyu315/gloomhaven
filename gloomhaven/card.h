#pragma once
#include<iostream>
#include<vector>
#include<string>

using namespace std;

class cardValue
{
public:
	cardValue();
	cardValue(int newAttack, int newShield, int newMove, int newRange, int newHeal);
	/*void setAttack(int);
	void setShield(int);
	void setMove(int);
	void setRange(int);
	void setHeal(int);*/
private:
	int attack;
	int shield;
	int move;
	int range;
	int heal;
};
class card:public cardValue
{
public:
	card();
	card(int newCardNumber, int newCardDex, vector<string> newUpperSkill, vector<string> newLowerSkill);
	void setCardNumber(int);
	void setCardDex(int);
	void setUpperSkill(vector<string>);
	void setLowerSkill(vector<string>);
	int getCardNumber() const;
	int getCardDex() const;
	vector<string> getUpperSkill();
	vector<string> getLowerSkill();
private:
	int cardNumber;
	int cardDex;
	vector<string> upperSkill;
	vector<string> lowerSkill;
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
	upperSkill.clear();
	lowerSkill.clear();
}
card::card(int newCardNumber, int newCardDex, vector<string> newUpperSkill, vector<string> newLowerSkill)
{
	cardNumber = newCardNumber;
	cardDex = newCardDex;
	upperSkill.assign(newUpperSkill.begin(), newUpperSkill.end());
	lowerSkill.assign(newLowerSkill.begin(), newLowerSkill.end());
}
void card::setCardNumber(int newCardNumber)
{
	cardNumber = newCardNumber;
}
void card::setCardDex(int newCardDex)
{
	cardDex = newCardDex;
}
void card::setUpperSkill(vector<string> newUpperSkill)
{
	upperSkill.assign(newUpperSkill.begin(),newUpperSkill.end());
}
void card::setLowerSkill(vector<string> newLowerSkill)
{
	lowerSkill.assign(newLowerSkill.begin(),newLowerSkill.end());
}
int card::getCardNumber() const
{
	return cardNumber;
}
int card::getCardDex() const
{
	return cardDex;
}
vector<string> card::getUpperSkill()
{
	return upperSkill;
}
vector<string> card::getLowerSkill()
{
	return lowerSkill;
}