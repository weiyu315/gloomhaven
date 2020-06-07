#pragma once
#include"base.h"

class character
{
public:
	character();
	character(string newName, int newMax_hp, int newHand_card_amount, int newTotal_card_amount);

	string name = "";
	int max_hp = 0;

	vector<card> total_card;//所有卡牌
	int total_card_amount = 0;//此生物總共有的卡牌數量

	vector<card> hand_card;//手牌 資料庫不使用
	int hand_card_amount = 0;//可選用卡牌數

	card using_card[2] = {};//正在使用的兩張牌
	void setUsing_card(int index, int newUsing_card_number, card newUsing_card[2], vector<card> newHand_card);

	int locate_x = 0;
	int locate_y = 0;
	string map_name = "";//在地圖上顯示的名字 A、B、C等等

	bool long_rest = false;
	int round_dex = 0;//本輪敏捷值
	int round_hp = 0;//本輪血量
	vector<card> discard_card;//棄牌堆
};