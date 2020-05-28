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
	vector<int>card_action;//0為move,1為attack,2為shield,3為heal
	vector<vector<int>>card_action_value;//紀錄卡牌動作的值，attack值第二個為range;move w=0 a=1 s=2 d=3
	int return_value;//是否有重洗標誌
public:
	void Set_card_number(int new_number);
	void Set_card_agility(int new_agility);
	void Set_card_action(string new_action);
	void Set_card_value(string new_value);
	void Set_return_value(string new_return_value);
	void Set_attack_range(string new_attack_range);
	
	int Get_card_number();
	int Get_card_agility();
	vector<int> Get_card_action();
	vector<vector<int>> Get_card_action_value();
	int Get_return_value();

	void rezero();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
void monster_card::Set_card_number(int new_number) {
	card_number = new_number;
};
void monster_card::Set_card_agility(int new_agility) {
	card_agility = new_agility;
};
void monster_card::Set_card_action(string new_action) {
	if (new_action == "move") {
		card_action.push_back(0);
	}
	else if(new_action == "attack") {
		card_action.push_back(1);
	}
	else if (new_action == "shield") {
		card_action.push_back(2);
	}
	else if (new_action == "heal") {
		card_action.push_back(3);
	}
	else {
		cout<< new_action << "讀取錯誤"<<"\n";
	}
};
void monster_card::Set_card_value(string new_value) {
	vector<int> input;
	if (card_action[card_action.size() - 1] == 0) {
		for (int i = 0; i < new_value.size(); i++) {
			if (new_value[i] == 'w') {
				input.push_back(0);
			}
			else if (new_value[i] == 'a') {
				input.push_back(1);
			}
			else if (new_value[i] == 's') {
				input.push_back(2);
			}
			else if (new_value[i] == 'd') {
				input.push_back(3);
			}
		}
	}
	else if (card_action[card_action.size() - 1] >= 1|| card_action[card_action.size() - 1] <=3) {
		input.push_back(atoi(new_value.c_str()));
	}
	card_action_value.push_back(input);
};
void monster_card::Set_return_value(string new_return_value) {
	if (new_return_value == "d") {
		return_value = 0;
	}
	else if (new_return_value == "r") {
		return_value = 1;
	}
};
void monster_card::Set_attack_range(string new_attack_range) {
	card_action_value[card_action_value.size() - 1].push_back(atoi(new_attack_range.c_str()));
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int monster_card::Get_card_number() {
	return card_number;
};
int monster_card::Get_card_agility() {
	return card_agility;
};
vector<int> monster_card::Get_card_action() {
	return card_action;
};
vector<vector<int>> monster_card::Get_card_action_value() {
	return card_action_value;
};
int monster_card::Get_return_value() {
	return return_value;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void monster_card::rezero() {
	card_number=0;
	card_agility=0;
	card_action.clear();
	card_action_value.clear();
	return_value=0;
};