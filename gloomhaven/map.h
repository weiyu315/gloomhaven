#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"monster.h"
#include"evil_guy.h"

class map {
private:
	vector<vector<int>> original_map;
	vector<vector<bool>> cout_map;//0������ܡA1�����
	int hight;
	int width;
	int startlocation_x[4];//�x�s�_�l�i��ܪ���m
	int startlocation_y[4];
	int start_point_x;//�x�s�@�}�l*����m
	int start_point_y;
	vector<int>hero_location_x;//�x�s�}���ܫ᪺��l
	vector<int>hero_location_y;
	/*---------------------------------------------------------------*/
	vector<int> door_x;//������m
	vector<int> door_y;
	vector<bool> door_open_or_close;//���O�_�}��
	/*===============================================================*/
	vector<string> monster_name;
	vector<char>monster_char_name;//�Ǫ��b�a�ϤW���W�r
	vector<int>monster_location_x;
	vector<int>monster_location_y;
	vector<int>monster_status[3];
public:
	map();
	map(string file_map);
	void Set_map_size(int h,int w);//�x�s�a�Ϥj�p
	void Set_map(string n);//�x�s�a�ϸ�T
	void Set_startlocation(int x,int y,int n);
	void Set_monster_information(string name,int x,int y,int one,int two,int three,int i);
	void Set_initialization_point();//��l�Ƥ@�}�l��point
	bool Set_start_point();//��ܤ@�}�l����m
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	int Get_monster_quaility();//�o��Ǫ����ƶq
	string Get_monster_name(int n);
	char Get_monster_char_name(int n);
	int Get_monster_location_x(int n);
	int Get_monster_location_y(int n);
	int Get_monster_status(int n,int hero_qualify);
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	void initalization_map(int x,int y);//��l�Ʀa��
	void output_decide_map(vector<evil_guy> Monster);
	void output(vector<evil_guy> Monster);
	char output_point_map(int x,int y,vector<evil_guy> Monster,int level);//level 0��ܬ���ܪ��A�Alevel1��ܬ����`
};
map::map() {
	hight = 0;
	width = 0;
	original_map.clear();
	cout_map.clear();
};
map::map(string file_map) {
	fstream file;
	string n;//��file��X���Ȧs��
	int front, back;//���ӦP�ɿ�J��int
	int one, two, three;//��J��ӡB�T�ӡB�Υ|�ӤH�ɪ�����
	int time;

	file.open(file_map, ios::in);
	if (!file) {
		cout << "�䤣��a��" << "\n";
	}
	else {
		file >> front >> back;
		Set_map_size(front,back);
		for (int i = 0; i < hight; i++) {
			file >> n;
			Set_map(n);
		}
		for (int i = 0; i < 4; i++) {
			file >> front >> back;//front��x�ȡAback��y��
			Set_startlocation(front, back, i);
		}
		initalization_map(startlocation_x[0],startlocation_y[0]);
		file >> time;//��J����
			for(int i = 0; i < time;i++) {
			file >> n >> front >> back >> one >> two >> three;
			Set_monster_information(n,front,back, one, two,three,i);
		}
	}
	file.close();
};
bool map::Set_start_point() {
	string move;//���ʫ��O
	cin >> move;
	bool does;

	for (int i = 0; i < move.size(); i++) {
		does = false;
		if (move[i]=='w') {
			for(int j=0;j<4;j++){
				if (start_point_x == startlocation_x[j] && start_point_y-1 == startlocation_y[j]) {
					for (int k=0; k < hero_location_x.size(); k++) {
						if (hero_location_x[k] == startlocation_x[j] && hero_location_y[k] == startlocation_y[j]) {
							does = true;
						}
					}
					if (does == false) {
						start_point_x = startlocation_x[j];
						start_point_y = startlocation_y[j];
						j = 4;
					}
				}
			}
		}
		else if (move[i] == 'a') {
			for (int j = 0; j < 4; j++) {
				if (start_point_x-1 == startlocation_x[j] && start_point_y == startlocation_y[j]) {
					for (int k=0; k < hero_location_x.size(); k++) {
						if (hero_location_x[k] == startlocation_x[j] && hero_location_y[k] == startlocation_y[j]) {
							does = true;
						}
					}
					if (does == false) {
						start_point_x = startlocation_x[j];
						start_point_y = startlocation_y[j];
						j = 4;
					}
				}
			}
		}
		else if (move[i] == 's') {
			for (int j = 0; j < 4; j++) {
				if (start_point_x == startlocation_x[j] && start_point_y + 1 == startlocation_y[j]) {
					for (int k=0; k < hero_location_x.size(); k++) {
						if (hero_location_x[k] == startlocation_x[j] && hero_location_y[k] == startlocation_y[j]) {
							does = true;
						}
					}
					if (does == false) {
						start_point_x = startlocation_x[j];
						start_point_y = startlocation_y[j];
						j = 4;
					}
				}
			}
		}
		else if (move[i] == 'd') {
			for (int j = 0; j < 4; j++) {
				if (start_point_x + 1 == startlocation_x[j] && start_point_y == startlocation_y[j]) {
					for (int k=0; k < hero_location_x.size(); k++) {
						if (hero_location_x[k] == startlocation_x[j] && hero_location_y[k] == startlocation_y[j]) {
							does = true;
						}
					}
					if (does == false) {
						start_point_x = startlocation_x[j];
						start_point_y = startlocation_y[j];
						j = 4;
					}
				}
			}
		}
		else if (move[i] == 'e') {

		}
		else {
			cout << "���ʫ��O��J���~\n";
			return 0;
		}
	}
	hero_location_x.push_back(start_point_x);
	hero_location_y.push_back(start_point_y);
	return 1;
};
void map::Set_map_size(int h, int w) {
	vector<bool> save_information;//�Ȧs�ɮ�

	cout_map.clear();
	if (h >= 0 && w >= 0) {
		hight = h;
		width = w;
		for (int i = 0; i < hight; i++) {
			for (int j = 0; j < width; j++) {
				save_information.push_back(0);
			}
			cout_map.push_back(save_information);
			save_information.clear();
		}
	}
	else {
		cout << "�榡���~\n";
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////
void map::Set_map(string n) {
	vector<int>temproary;
	if (width == n.size()) {
		for (int i = 0; i < width; i++) {
			if (n[i] == '0') {
				temproary.push_back(0);
			}
			else if (n[i] == '1') {
				temproary.push_back(1);
			}
			else if (n[i] == '2') {
				temproary.push_back(2);
			}
			else if (n[i] == '3') {
				temproary.push_back(3);
				door_x.push_back(i);
			    door_y.push_back(temproary.size()+1);
				door_open_or_close.push_back(0);
			}
			else {
				cout << "�a�ϸ��J���~\n";
			}
		}
		original_map.push_back(temproary);
		temproary.clear();
	}
	else {
		cout << "�e�פ���\n";
	}
};
////////////////////////////////////////////////////////////////////////////////////////
void map::initalization_map(int x,int y) {
	cout_map[y][x] = 1;
	if (original_map[y][x] == 3) {
		for (int i = 0; i < door_x.size(); i++) {
			if (door_x[i] == x && door_y[i] == y) {
				if (door_open_or_close[i] == 0) {
					return;
				}
			}
		}
	}
		if (original_map[y+1][x] == 1|| original_map[y+1][x] == 2|| original_map[y + 1][x] == 3) {
			if (cout_map[y + 1][x] == 0) {
				initalization_map(x, y + 1);
			}
	}
		if (original_map[y][x+1] == 1 || original_map[y][x+1] == 2|| original_map[y][x+1] == 3) {
			if (cout_map[y][x+1] == 0) {
				initalization_map(x + 1, y);
			}
		}
		if (original_map[y - 1][x] == 1 || original_map[y - 1][x] == 2|| original_map[y - 1][x] == 3) {
			if (cout_map[y - 1][x] == 0) {
				initalization_map(x, y - 1);
			}
		}
		if (original_map[y][x-1] == 1 || original_map[y][x-1] == 2|| original_map[y][x - 1] == 3) {
			if (cout_map[y][x-1] == 0) {
				initalization_map(x-1, y);
			}
		}

};
////////////////////////////////////////////////////////////////////////////////////
void map::Set_initialization_point() {
	bool does;
	for (int i = 0; i <4; i++) {
		does = false;
		for (int j = 0; j < hero_location_x.size(); j++) {
			if (hero_location_x[j] == startlocation_x[i]&& hero_location_y[j] == startlocation_y[i]) {
				does = true;
			}
		}
		if (does == false) {
			start_point_x = startlocation_x[i];
			start_point_y = startlocation_y[i];
		}
	}
	hero_location_x;//�x�s�}���ܫ᪺��l
	hero_location_y;
	for (int i = 0; i < 4; i++) {
		if (start_point_y > startlocation_y[i]|| (start_point_y == startlocation_y[i]&& start_point_x > startlocation_x[i])) {
			does = false;
			for (int j = 0; j < hero_location_x.size(); j++) {
				if (hero_location_x[j] == startlocation_x[i] && hero_location_y[j] == startlocation_y[i]) {
					does = true;
				}
			}
			if (does == false) {
				start_point_x = startlocation_x[i];
				start_point_y = startlocation_y[i];
			}
		}
	}

	
};
//////////////////////////////////////////////////////////////////////////////////////////////
void map::Set_startlocation(int x, int y, int n) {
	startlocation_x[n]=x;
	startlocation_y[n]=y;
};
void map::Set_monster_information(string name, int x, int y, int one, int two, int three,int i) {
	monster_name.push_back(name);
	monster_char_name.push_back(i + 'a');
	monster_location_x.push_back(x);
	monster_location_y.push_back(y);
	monster_status[0].push_back(one);
	monster_status[1].push_back(two);
	monster_status[2].push_back(three);
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int map::Get_monster_quaility() {
	return monster_location_x.size();
};
char map::Get_monster_char_name(int n) {
	return monster_char_name[n];
};
string map::Get_monster_name(int n) {
	return monster_name[n];
};
int map::Get_monster_location_x(int n) {
	return monster_location_x[n];
};
int map::Get_monster_location_y(int n) {
	return monster_location_y[n];
};
int map::Get_monster_status(int n, int hero_qualify) {
return monster_status[hero_qualify-2][n];
};
////////////////////////////////////////////////////////////////////////////////////////////////
void map::output_decide_map(vector<evil_guy> Monster) {
	for (int i = 0; i < hight; i++) {
		for (int j = 0; j < width; j++) {
			if (cout_map[i][j] == 0) {
				cout << " ";
			}
			else {
				cout<<output_point_map(j, i, Monster, 0);
			}
		}
		cout << "\n";
	}
};/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void map::output(vector<evil_guy> Monster) {
	for (int i = 0; i < hight; i++) {
		for (int j = 0; j < width; j++) {
			if (cout_map[i][j] == 0) {
				cout << " ";
			}
			else {
				cout << output_point_map(j, i, Monster, 1);
			}
		}
		cout << "\n";
  }
};////////////////////////////////////////////////////////////////////////////////////////////////////////////
char map::output_point_map(int x, int y, vector<evil_guy> Monster, int level) {
	if (level == 0) {
		for (int i = 0; i < 4; i++) {
			if (startlocation_x[i] == x && startlocation_y[i] == y) {
				if (start_point_x == x && start_point_y == y) {
					return '*';
				}
				else {
					for (int j = 0; j < hero_location_x.size(); j++) {
						if (x == hero_location_x[j] && y == hero_location_y[j]) {
							return 'A' + j;
						}
					}
				}
				return '_';
			}
		}
		for (int i = 0; i < Monster.size(); i++) {
			if (Monster[i].Get_x() == x && Monster[i].Get_y() == y) {
				return Monster[i].Get_monster_card_name();
			}
		}
		return original_map[y][x]+48;
	}
	if (level == 1) {
		for (int j = 0; j < hero_location_x.size(); j++) {
			if (x == hero_location_x[j] && y == hero_location_y[j]) {
				return 'A' + j;
			}
		}
		for (int i = 0; i < Monster.size(); i++) {
			if (Monster[i].Get_x() == x && Monster[i].Get_y() == y) {
				return Monster[i].Get_monster_card_name();
			}
		}
		return original_map[y][x] + 48;
	}
};