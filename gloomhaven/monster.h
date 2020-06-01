#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"monster_card.h"

using namespace std;

class monster {//�����Ǫ�����Ʈw
private:
	vector<string> monster_name;
	vector<int>monster_attack[2];//0�����q�A1����^�C
	vector<int>monster_hp[2];
	vector<int>monster_range[2];
	vector<vector<monster_card>>card;
	int monster_quantity;//���~�ƶq
public:
	monster();
	monster(string  file_monster);
	void Set_Monster_Name(string new_monster_name);
	void Set_Monster_hp(int new_hp, int normal_or_elite);//�x�s�ͩR
	void Set_Monster_Attack(int new_attack,int normal_or_elite);//�x�s�����᭱�ǤJ���Ȭ��P�_�O�_����^��
	void Set_Monster_range(int new_hp, int normal_or_elite);//�x�s�g�{
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	string Get_Monster_Name(int number);
	int Get_Monster_hp(int number, int normal_or_elite);
	int Get_Monster_Attack(int number, int normal_or_elite);
	int Get_Monster_range(int number, int normal_or_elite);
	vector<monster_card> Get_Monster_Card(int new_card);
	int Get_Monster_number();
};
monster::monster() {
	monster_name.clear();
	for (int i = 0; i <= 1; i++) {
		monster_attack[i].clear();
		monster_hp[i].clear();
		monster_range[i].clear();
	}
	for (int i = 0; i < card.size(); i++) {
		card[i].clear();
	}
	monster_quantity = 0;
};
monster::monster(string  file_monster) {
	
	fstream file;
	string n;//�s��file����X
	monster_card temporarily_card;
	vector<monster_card> vector_temporarily_card;

	file.open(file_monster , ios::in);//Ū��
	if (!file) {
		cout << "�䤣��Ǫ����ɮ�\n";
	}
	else {
		file>> monster_quantity;
		file >> n;

		for (int i = 0; i < monster_quantity; i++) 
		{
			Set_Monster_Name(n);

			for (int j = 0; j <= 1; j++) {
				file >> n;
				Set_Monster_hp(atoi(n.c_str()), j);
				file >> n;
				Set_Monster_Attack(atoi(n.c_str()), j);
				file >> n;
				Set_Monster_range(atoi(n.c_str()), j);
			}
			
			file >> n;
			while (n == monster_name[i]) {
				file >> n;
				temporarily_card.Set_card_number(atoi(n.c_str()));

				file >> n;
				temporarily_card.Set_card_agility(atoi(n.c_str()));

				file >> n;
				while (n != "r" && n != "d") {
					if (n != "range") {
						temporarily_card.Set_card_action(n);
						file >> n;
						temporarily_card.Set_card_value(n);
						file >> n;
					}
					else {
						file >> n;
						temporarily_card.Set_attack_range(n);
						file >> n;
					}
				}
				temporarily_card.Set_return_value(n);
				vector_temporarily_card.push_back(temporarily_card);
				temporarily_card.rezero();
				if (!file.eof()) {
					file >> n;
				}
			}
			card.push_back(vector_temporarily_card);
			vector_temporarily_card.clear();
		}
	}
	file.close();
};
void monster::Set_Monster_Name(string new_monster_name) {
	monster_name.push_back(new_monster_name);
};
void monster::Set_Monster_hp(int new_hp, int normal_or_elite) {
	monster_hp[normal_or_elite].push_back(new_hp);
};
void monster::Set_Monster_Attack(int new_attack, int normal_or_elite) {
	monster_attack[normal_or_elite].push_back(new_attack);
};
void monster::Set_Monster_range(int new_range, int normal_or_elite) {
	monster_range[normal_or_elite].push_back(new_range);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
string monster::Get_Monster_Name(int number) {
	return monster_name[number];
};
int monster::Get_Monster_hp(int number, int normal_or_elite) {
	return monster_hp[normal_or_elite][number];
};
int monster::Get_Monster_Attack(int number, int normal_or_elite) {
	return monster_attack[normal_or_elite][number];
};
int monster::Get_Monster_range(int number, int normal_or_elite) {
	return monster_range[normal_or_elite][number];
};
vector<monster_card> monster::Get_Monster_Card(int number) {
	return card[number];
};
int monster::Get_Monster_number() {
	return monster_name.size();
};