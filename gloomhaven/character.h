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
	bool setUsing_card(int index, int newUsing_card_number, card newUsing_card[2], vector<card> newHand_card);

	int locate_x = 0;
	int locate_y = 0;
	char map_name;//在地圖上顯示的名字 A、B、C等等

	bool long_rest = false;
	int round_dex = 0;//本輪敏捷值
	int round_order;//4-3本輪順序(海靜加的)
	int round_hp = 0;//本輪血量
	int round_shield = 0;//本輪護甲值
	bool alive = true;//角色是(true)否(false)存活
	bool choose_using_card = false;//角色是(true)否(false)已選擇要出的牌
	int discard_card_amount = 0;//棄牌數量
	//vector<card> discard_card;//棄牌堆
};