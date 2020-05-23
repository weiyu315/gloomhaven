#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

class monster_card {
private:
	int card_number;
	int card_agility;//敏捷值
	int card_time;//紀錄卡牌有幾個動作
	vector<int>card_action;//0為move,1為attack,2為shield,3為heal
	vector<int>card_action_value;//紀錄卡牌動作的值，attack值第二個為range
	int return_value;//是否有重洗標誌
public:
    void Set_card_number(int new_number);
	void Set_card_agility(int new_agility);
	void Set_card_time(int new_time);
	void Set_card_action();
	void Set_card_action_value();
	void Set_return_value();
};