#pragma once
#include"base.h"

class character
{
public:
	character();
	character(string newName, int newMax_hp, int newHand_card_amount, int newTotal_card_amount);

	string name = "";
	int max_hp = 0;

	vector<card> total_card;//┮Τ礟
	int total_card_amount = 0;//ネ羆Τ礟计秖

	vector<card> hand_card;//も礟 戈畐ぃㄏノ
	int hand_card_amount = 0;//匡ノ礟计

	card using_card[2] = {};//タㄏノㄢ眎礟
	void setUsing_card(int index, int newUsing_card_number, card newUsing_card[2], vector<card> newHand_card);

	int locate_x = 0;
	int locate_y = 0;
	string map_name = "";//瓜陪ボ ABC单单

	bool long_rest = false;
	int round_dex = 0;//セ近庇倍
	int round_hp = 0;//セ近﹀秖
};