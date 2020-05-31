#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"monster.h"
class map {
private:
	vector<vector<int>> original_map;
	int hight;
	int width;
	int startlocation_x[4];//儲存起始可選擇的位置
	int startlocation_y[4];
	vector<string> monster_name;
	vector<int>monster_location_x;
	vector<int>monster_location_y;
	vector<int>monster_status[3];
public:
	map();
	map(string file_map);
	void Set_map_size(int h,int w);//儲存地圖大小
	void Set_map(string n);//儲存地圖資訊
	void Text();//測試用
	void Set_startlocation(int x,int y,int n);
	void Set_monster_information(string name,int x,int y,int one,int two,int three);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	int Get_monster_quaility();//得到怪物的數量
	string Get_monster_name(int n);
	int Get_monster_location_x(int n);
	int Get_monster_location_y(int n);
	int Get_monster_status(int n,int hero_qualify);
};
map::map() {
	hight = 0;
	width = 0;
	original_map.clear();
};
map::map(string file_map) {
	fstream file;
	string n;//放file輸出的暫存器
	int front, back;//放兩個同時輸入的int
	int one, two, three;
	int time;

	file.open(file_map, ios::in);
	if (!file) {
		cout << "找不到地圖" << "\n";
	}
	else {
		file >> front >> back;
		Set_map_size(front,back);
		for (int i = 0; i < hight; i++) {
			file >> n;
			Set_map(n);
		}
		for (int i = 0; i < 4; i++) {
			file >> front >> back;//front為x值，back為y值
			Set_startlocation(front, back, i);
		}
		file >> time;//輸入次數
			for(int i = 0; i < time;i++) {
			file >> n >> front >> back >> one >> two >> three;
			Set_monster_information(n,front,back, one, two,three);
		}
	}
	file.close();
};
void map::Set_map_size(int h, int w) {
	if (h >= 0 && w >= 0) {
		hight = h;
		width = w;
	}
	else {
		cout << "格式錯誤\n";
	}
};
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
void map::Text() {
	cout << "長" << hight << "  寬" << width << "\n";
	for (int i = 0; i < original_map.size(); i++) {
		for (int j = 0; j < original_map[i].size(); j++) {
			cout << original_map[i][j];
		}
		cout << "\n";
	}
	for (int i = 0; i < 4; i++) {
		cout<<"起始位置"<<i<<"   x"<< startlocation_x[i]<<"   y"<<startlocation_y[i]<<"\n";
	}
	for (int i = 0; i < monster_name.size(); i++) {
		cout << "怪獸名字" << monster_name[i] << "  x" << monster_location_x[i] << "  y" << monster_location_y[i]<<"   "<< monster_status[0][i]<<monster_status[1][i]<<monster_status[2][i]<<"\n";
	}
};
void map::Set_startlocation(int x, int y, int n) {
	startlocation_x[n]=x;
	startlocation_y[n]=y;
};
void map::Set_monster_information(string name, int x, int y, int one, int two, int three) {
	monster_name.push_back(name);
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