#pragma once
#include<iostream>
#include <Cmath>
#include <math.h>
#include<string>
#include<vector>
#include<fstream>
#include"monster.h"
#include"evil_guy.h"
#include"character.h"

class map {
private:
	vector<vector<int>> original_map;
	vector<vector<bool>> cout_map;//0為不顯示，1為顯示
	int hight;
	int width;
	int startlocation_x[4];//儲存起始可選擇的位置
	int startlocation_y[4];
	int start_point_x;//儲存一開始*的位置
	int start_point_y;
	/*---------------------------------------------------------------*/
	vector<int> door_x;//門的位置
	vector<int> door_y;
	vector<bool> door_open_or_close;//門是否開啟
	/*===============================================================*/
	vector<string> monster_name;
	vector<char>monster_char_name;//怪物在地圖上的名字
	vector<int>monster_location_x;
	vector<int>monster_location_y;
	vector<int>monster_status[3];
public:
	map();
	map(string file_map);
	void Set_map_size(int h,int w);//儲存地圖大小
	void Set_map(string n);//儲存地圖資訊
	void Set_startlocation(int x,int y,int n);
	void Set_monster_information(string name,int x,int y,int one,int two,int three,int i);
	void Set_initialization_point();//初始化一開始的point
	bool Set_start_point();//選擇一開始的位置
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	int Get_monster_quaility();//得到怪物的數量
	string Get_monster_name(int n);
	char Get_monster_char_name(int n);
	int Get_monster_location_x(int n);
	int Get_monster_location_y(int n);
	int Get_monster_status(int n,int hero_qualify);
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool initalization_map(int x,int y);//初始化地圖
	void output_decide_map(vector<evil_guy> Monster);
	void output(vector<evil_guy> Monster);
	char output_point_map(int x,int y,vector<evil_guy> Monster,int level);//level 0表示為選擇狀態，level1表示為正常
	void monster__action();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool monster_decide(int x,int y);// 4-1 判斷怪物是否在顯示地圖內
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool distant(char character_name,char monster_name,int dist);
	bool see(int c_x, int c_y, int m_x,int m_y);
	int attack_range(int c_x, int c_y, int m_x, int m_y,int step);
	void move(char c_name,int wafe, vector<evil_guy> Monster);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	vector<int>hero_location_x;//儲存腳色選擇後的位子
	vector<int>hero_location_y;
	vector<int>hero_char_name;
};
map::map() {
	hight = 0;
	width = 0;
	original_map.clear();
	cout_map.clear();
};
map::map(string file_map) {
	fstream file;
	string map_input;
	string n;//放file輸出的暫存器
	int front, back;//放兩個同時輸入的int
	int one, two, three;//輸入兩個、三個、或四個人時的等級
	int time;
	int a = 0;
	while (1) {
		if (a == 0) {
			map_input = file_map;
		}
		else {
			cin >> map_input;
		}
		a++;
		file.open(map_input, ios::in);
		if (!file) {
			cout << "找不到地圖" << "\n";
		}
		else {
			file >> front >> back;
			Set_map_size(front, back);
			for (int i = 0; i < hight; i++) {
				file >> n;
				Set_map(n);
			}
			for (int i = 0; i < 4; i++) {
				file >> front >> back;//front為x值，back為y值
				Set_startlocation(front, back, i);
			}
			initalization_map(startlocation_x[0], startlocation_y[0]);
			file >> time;//輸入次數
			for (int i = 0; i < time; i++) {
				file >> n >> front >> back >> one >> two >> three;
				Set_monster_information(n, front, back, one, two, three, i);
			}
			file.close();
			return;
		}
		file.close();
	};
}
bool map::Set_start_point() {
	string move;//移動指令
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
			cout << "移動指令輸入錯誤\n";
			return 0;
		}
	}
	hero_char_name.push_back('A' + hero_char_name.size() );
	hero_location_x.push_back(start_point_x);
	hero_location_y.push_back(start_point_y);
	return 1;
};
void map::Set_map_size(int h, int w) {
	vector<bool> save_information;//暫存檔案

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
		cout << "格式錯誤\n";
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
				cout << "地圖載入錯誤\n";
			}
		}
		original_map.push_back(temproary);
		temproary.clear();
	}
	else {
		cout << "寬度不對\n";
	}
};
////////////////////////////////////////////////////////////////////////////////////////
bool map::initalization_map(int x, int y) {
	int ds=0;
	if (cout_map[y][x] == 0) {
		ds = 1;
	}
	cout_map[y][x] = 1;
	if (original_map[y][x] == 3) {
		for (int i = 0; i < door_x.size(); i++) {
			if (door_x[i] == x && door_y[i] == y) {
				if (door_open_or_close[i] == 0) {
					return 0;
				}
			}
		}
	}
		if (original_map[y+1][x] == 1|| original_map[y+1][x] == 2|| original_map[y + 1][x] == 3) {
			if (cout_map[y + 1][x] == 0) {
				ds = 1;
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
				ds = 1;
				initalization_map(x, y - 1);
			}
		}
		if (original_map[y][x-1] == 1 || original_map[y][x-1] == 2|| original_map[y][x - 1] == 3) {
			if (cout_map[y][x-1] == 0) {
				ds = 1;
				initalization_map(x-1, y);
			}
		}
		return ds;
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
	hero_location_x;//儲存腳色選擇後的位子
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
							
							return hero_char_name[j];
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
				return hero_char_name[j];
			}
		}
		for (int i = 0; i < Monster.size(); i++) {
			if (Monster[i].Get_x() == x && Monster[i].Get_y() == y) {
				if (Monster[i].live_or_die == 1) {
					return Monster[i].Get_monster_card_name();
				}
			}
		}
		return original_map[y][x] + 48;
	}
};
bool map::monster_decide(int x, int y) {
	return cout_map[y][x];
};
bool map::distant(char character_name, char monster_name, int dist){
	int m_x=0;
	int m_y=0;
	int c_x=0;
	int c_y=0;
	for (int i = 0; i < hero_char_name.size(); i++) {
		if (character_name == hero_char_name[i]) {
			 c_x=hero_location_x[i];
			 c_y= hero_location_y[i];
		}
	}
	for (int i = 0; i < monster_char_name.size(); i++) {
		if (monster_name == monster_char_name[i]) {
			m_x= monster_location_x[i];
			m_y= monster_location_y[i];
		}
	}
	bool does=see(c_x,c_y,m_x,m_y);
	if (does == true) {
		vector<bool>save_information;
			for (int i = 0; i < hight; i++) {
				for (int j = 0; j < width; j++) {
					save_information.push_back(0);
				}
				save_information.clear();
			}
			if (attack_range(c_x, c_y, m_x, m_y, 0) <= dist|| (attack_range(c_x, c_y, m_x, m_y, 0)==1&&dist==0)) {
				return true;
			}
			else {
				return false;
			}
	}
	if (does == false) {
		return 0;
	}
};
bool map::see(int c_x, int c_y, int m_x, int m_y) {
	double d_x = c_x - m_x;
	double d_y = c_y - m_y;
	d_x = d_x / 100;
	d_y = d_y / 100;
	double i = m_x;
	double j = m_y;
 	for (;floor(j)!=c_y|| floor(i) != c_x;) {
		if (original_map[floor(j)][floor(i)] == 0) {
		return false;
	}
	i = i + d_x;
	j = j + d_y;
}
	return true;
};
int map::attack_range(int c_x,int c_y,int m_x,int m_y,int range) {
	int d_x = c_x - m_x;
	int d_y = c_y - m_y;
	if (d_x >= 0 && d_y >= 0) {
		return d_x + d_y;
	}
	if (d_x < 0 && d_y >= 0) {
		return -d_x + d_y;
	}
	if (d_x >= 0 && d_y < 0) {
		return d_x - d_y;
	}
	if (d_x < 0 && d_y < 0) {
		return -d_x - d_y;
	}
};
void map::move(char c_name,int wafe,vector<evil_guy> Monster) {
	string wave;
	bool ture=true;
	bool ture2 = true;
	int x;
	int y;
	while (ture2 == true){
		while (ture == true) {
			cout << "move command: ";
			cin >> wave;
			ture = false;
			ture2 = false;
			if (wave.size() > wafe) {
				ture = true;
			}
			for (int i = 0; i < wave.size(); i++) {
				if (wave[i] != 'w' && wave[i] != 'a' && wave[i] != 's' && wave[i] != 'd') {
					if (wave[i] == 'e' && wave.size() == 1) {

					}
					else {
						ture = true;
					}
				}
			}
			if (ture == true) {
				cout << "error move!!!" << endl;
			}
		}
		ture = true;
			for (int i = 0; i < hero_char_name.size(); i++) {
				if (hero_char_name[i] == c_name) {
					x = hero_location_x[i];
					y = hero_location_y[i];
				}
			}
			////////////////////////////////
			for (int i = 0; i < wave.size(); i++) {
				if (wave[i] == 'w') {
					y--;
				}
				if (wave[i] == 'a') {
					x--;
				}
				if (wave[i] == 's') {
					y++;
				}
				if (wave[i] == 'd') {
					x++;
				}
				
				for (int s = 0; s < Monster.size(); s++) {
					if (Monster[s].Get_x()==x&& Monster[s].Get_y()==y) {
						ture2 = true;
					}
				}
				if (i == wave.size() - 1) {
					for (int s = 0; s < hero_char_name.size(); s++) {
						if (hero_location_x[s] == x && hero_location_y[s] == y&&c_name!=hero_char_name[s]) {
							ture2 = true;
						}
					}
				}
				if (original_map[y][x] == 0 || original_map[y][x] == 2) {
					ture2= true;
					break;
				}
			}
			if (ture2 == true) {
				cout << "error move!!!" << endl;
			}
		}
	for (int i = 0; i < hero_char_name.size(); i++) {
		if (hero_char_name[i] == c_name) {
			hero_location_x[i] = x;
			hero_location_y[i] = y;
		}
	}
	if (original_map[y][x] == 3|| Monster.size()==0) {
		for (int i = 0; i < door_open_or_close.size(); i++) {
			if (door_x[i] == x && door_y[i]==y) {
				door_open_or_close[i] = 1;
			}
		}
	}
};