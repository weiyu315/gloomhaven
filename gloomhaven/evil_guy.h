#pragma once
#include<iostream>
#include"evil_guy.h"
#include"monster.h"
#include"map.h"
#include<stdlib.h>
#include<time.h>
//�����Ǫ�����T
//////////////////////////////////////////////////////////////////////////////////////////////////////

class evil_guy {

public:
	bool live_or_die;
	string monster_name;
	char monster_card_name;
	int monster_max_hp;//�Ǫ����̤j�ͩR��
	int monster_current_hp;//�Ǫ���e�ͩR
	int monster_current_shield = 0;
	int monster_attack;//�Ǫ���������
	int monster_range;//�Ǫ����g�{
	int x;//x��y���Ǫ�����m
	int y;
	vector<monster_card>card;//�Ǫ����P��
	vector<monster_card>throw_card;//�Ǫ���P��
	monster_card correct_card;
	int round_order;//4-3��������(���R�[��)
	void Set_correct_card(int input);
	/////////////////////////////////////////////////////////////////////////////////////////////
	void initialization_bad_guy(string monsters,char monster_char_name,int monster_location_x,int monster_location_y,int monster_status,monster a);//�]�w�Ǫ���l��
	void re_zero();//�M�Ÿ��
	void text();
	/////////////////////////////////////////////////////////////////////////////////////////////
	string Get_monster_name();
	int Get_x();
	int Get_y();
	int Get_correct_card();
	int Get_correct_card_agility();
	char Get_monster_card_name();
	void choise_action(int debug_Mode);
	void output();//4-2��X�ޯ�
};
void evil_guy::initialization_bad_guy(string monsters,char monster_char_name , int monster_location_x, int monster_location_y, int monster_status, monster a) {
	x = monster_location_x;
	y = monster_location_y;
	for (int i = 0; i < a.Get_Monster_number(); i++) {
		if (a.Get_Monster_Name(i) == monsters&&monster_status!=0) {
			monster_name= a.Get_Monster_Name(i);
			monster_card_name=monster_char_name;
			monster_max_hp=a.Get_Monster_hp(i,monster_status-1);
			monster_current_hp= monster_max_hp;
			monster_attack=a.Get_Monster_Attack(i,monster_status-1);
		     monster_range= a.Get_Monster_range(i, monster_status - 1);
			 card = a.Get_Monster_Card(i);
		}
	}
};
void evil_guy::re_zero() {};
void evil_guy::text() {
	cout << correct_card.Get_card_number() << " " << correct_card.Get_card_agility();
};
//////////////////////////////////////////////////////////////////////////////////////////
int evil_guy::Get_x() { return x; };
int evil_guy::Get_y() { return y; };
char evil_guy::Get_monster_card_name() { return monster_card_name; };
///////////////////////////////////////////////////////////////////////////////////////////////
void evil_guy::choise_action(int debug_Mode) {
	int which;
	if (debug_Mode == 0) {
		srand(time(NULL));
		int t = rand();
		which = t % card.size();
	}
	if (debug_Mode == 1) {
		 which=0;
		for (int i = 0; i < card.size(); i++) {
			if (card[which].Get_card_number() > card[i].Get_card_number()) {
				which = i;
			}
		}
	}
	correct_card = card[which];
};
string evil_guy::Get_monster_name() {
	return monster_name;
};
void evil_guy::Set_correct_card(int input) {
	correct_card = card[input];
};
int evil_guy::Get_correct_card() {
	return correct_card.Get_card_number();
};
void evil_guy::output() {
	cout << monster_name << " " ;
	correct_card.output();
	cout << "\n";
};
int evil_guy::Get_correct_card_agility() {
	return correct_card.Get_card_agility();
};