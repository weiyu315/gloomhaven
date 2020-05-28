#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"monster_card.h"

using namespace std;

class monster {//此為怪物的資料庫
private:
	vector<string> monster_name;
	vector<int>monster_attack[2];//0為普通，1為精英。
	vector<int>monster_hp[2];
	vector<int>monster_range[2];
	vector<vector<monster_card>>card;
	int monster_quantity;//怪獸數量
public:
	monster();
	monster(string  file_monster);
	void Set_Monster_Name(string new_monster_name);
	void Set_Monster_hp(int new_hp, int normal_or_elite);//儲存生命
	void Set_Monster_Attack(int new_attack,int normal_or_elite);//儲存攻擊後面傳入的值為判斷是否為精英怪
	void Set_Monster_range(int new_hp, int normal_or_elite);//儲存射程
	void test();
	
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
	string n;//存放file的輸出
	monster_card temporarily_card;
	vector<monster_card> vector_temporarily_card;

	file.open(file_monster , ios::in);//讀檔
	if (!file) {
		cout << "找不到怪物的檔案\n";
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
void monster::test(){
	vector<int>cardaction;
	vector<vector<int>>cardactionvalue;
	cout<<"怪獸有"<< monster_quantity<<"種"<<"\n";
	for (int i = 0; i < monster_quantity; i++) {
		cout << "第" << i + 1 << "隻叫" << monster_name[i] << "\n";
		cout << "普通生命" << monster_hp[0][i] <<" 攻擊"<< monster_attack[0][i]<<" 範圍" << monster_range[0][i]<<"\n";
		cout << "菁英生命" << monster_hp[1][i] << " 攻擊" << monster_attack[1][i] << " 範圍" << monster_range[1][i] << "\n";
		cout << "有" << card[i].size() << "張卡\n";
		for (int j = 0; j < card[i].size(); j++) {
			cout << "編號" << card[i][j].Get_card_number() << " 敏捷值" << card[i][j].Get_card_agility();
			cardaction = card[i][j].Get_card_action();
			cardactionvalue=card[i][j].Get_card_action_value();
			for (int k = 0;k< cardaction.size(); k++) {
				if (cardaction[k] == 0) {
					cout << " 移動";
					for (int r = 0; r < cardactionvalue[k].size(); r++) {
						if (cardactionvalue[k][r]==0) {
							cout << "上";
						}
						if (cardactionvalue[k][r] == 1) {
							cout << "左";
						}
						if (cardactionvalue[k][r] == 2) {
							cout << "下";
						}
						if (cardactionvalue[k][r] == 3) {
							cout << "右";
						}
					}
				}
				else if (cardaction[k] == 1) {
					cout << " 攻擊加"<< cardactionvalue[k][0]<<"點";
					if (monster_range[0][i] > 0) {
						cout << " 範圍加" << cardactionvalue[k][1] << "點";
					}
				}
				else if (cardaction[k] == 2) {
					cout << " 加固"<< cardactionvalue[k][0]<<"點";
				}
				else if (cardaction[k] == 3) {
					cout << " 回血"<< cardactionvalue[k][0]<<"點";
				}

			}
			cout << "\n";
		}
	}
}
