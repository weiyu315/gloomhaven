#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

class monster_card {
private:
	int card_number;
	int card_agility;//�ӱ���
	int card_time;//�����d�P���X�Ӱʧ@
	vector<int>card_action;//0��move,1��attack,2��shield,3��heal
	vector<int>card_action_value;//�����d�P�ʧ@���ȡAattack�ȲĤG�Ӭ�range
	int return_value;//�O�_�����~�лx
public:
    void Set_card_number(int new_number);
	void Set_card_agility(int new_agility);
	void Set_card_time(int new_time);
	void Set_card_action();
	void Set_card_action_value();
	void Set_return_value();
};