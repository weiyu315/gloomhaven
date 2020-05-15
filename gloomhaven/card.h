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
	void setUpperSkill(string);
	void setLowerSkill(string);
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

}