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
	vector<monster_card>card;
	int monster_quantity;
public:
	monster();
	monster(string  file_monster);
	void Set_Monster_Name(string new_monster_name);
	void Set_Monster_hp(int new_hp, int normal_or_elite);//�x�s�ͩR
	void Set_Monster_Attack(int new_attack,int normal_or_elite);//�x�s�����᭱�ǤJ���Ȭ��P�_�O�_����^��
	void Set_Monster_range(int new_hp, int normal_or_elite);//�x�s�g�{
	void test();
	
};
monster::monster() {
	monster_name.clear();
	for (int i = 0; i <= 1; i++) {
		monster_attack[i].clear();
		monster_hp[i].clear();
		monster_range[i].clear();
	}
	monster_quantity = 0;
};
monster::monster(string  file_monster) {
	
	fstream file;
	string n;//�s��file����X

	file.open(file_monster , ios::in);//Ū��
	if (!file) {
		cout << "�䤣��Ǫ����ɮ�\n";
	}
	else {
		file>> monster_quantity;
		cout << monster_quantity <<"\n";
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
			while (n==monster_name[i]) {

			}
			test();
		}
	}
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
void monster::test(){
	cout<<"name"<<monster_name[0]<<"\n";
	cout<<"normal attack" << monster_attack[0][0]<<"\n";
	cout<<"normal hp"<<monster_hp[0][0]<<"\n";
	cout<<"normal range"<<monster_range[0][0]<<"\n";
	cout << "elite attack" << monster_attack[1][0] << "\n";
	cout << "elite hp" << monster_hp[1][0] << "\n";
	cout << "elite range" << monster_range[1][0] << "\n";
}
