#pragma once
#include<iostream>
#include"evil_guy.h"
#include"monster.h"
#include"map.h"
//�����Ǫ�����T
//////////////////////////////////////////////////////////////////////////////////////////////////////

class evil_guy {
private:
	string monster_name;
	char monster_card_name;
	int monster_max_hp;//�Ǫ����̤j�ͩR��
	int monster_current_hp;//�Ǫ����e�ͩR
	int monster_attack;//�Ǫ���������
	int monster_range;//�Ǫ����g�{
	int x;//x��y���Ǫ�����m
	int y;
	vector<monster_card>card;
public:
	void initialization_bad_guy(string monsters,int monster_location_x,int monster_location_y,int monster_status,monster a);//�]�w�Ǫ���l��
	void re_zero();//�M�Ÿ��
	void text();
};
void evil_guy::initialization_bad_guy(string monsters, int monster_location_x, int monster_location_y, int monster_status, monster a) {
	x = monster_location_x;
	y = monster_location_y;
	for (int i = 0; i < a.Get_Monster_number(); i++) {
		if (a.Get_Monster_Name(i) == monsters&&monster_status!=0) {
			monster_name= a.Get_Monster_Name(i);
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
	cout<<monster_name<<"\n";
	cout<<monster_max_hp<<"\n";//�Ǫ����̤j�ͩR��
	cout<<monster_current_hp<<"\n";//�Ǫ����e�ͩR
	cout<<monster_attack<<"\n";//�Ǫ���������
	cout<<monster_range<<"\n";//�Ǫ����g�{
	cout<<x<<"\n";//x��y���Ǫ�����m
	cout<<y<<"\n";
};