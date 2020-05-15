#pragma once
#include<iostream>
#include<vector>
#include<string>

using namespace std;

class card
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