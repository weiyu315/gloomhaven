#pragma once
#include"base.h"

class character
{
public:
	character();
	character(string newName, int newMax_hp, int newHand_card_amount, int newTotal_card_amount);

	string name = "";
	int max_hp = 0;
	vector<card> hand_card;//手牌 資料庫不使用
	int hand_card_amount = 0;//可選用卡牌數
	vector<card> total_card;//所有卡牌
	int total_card_amount = 0;//此生物總共有的卡牌數量
};