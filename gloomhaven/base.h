#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

struct skill
{
public:
	skill();
	skill(string newSkill_name, int newVal);
	skill(int newType, int newVal);

	void set_skill(string newSkill_name, int newVal);
	int type = -1;//0=>attack 1=>shield 2=>move 3=>heal
	int value = -1;
	int range = 0;//有attack才有range range0與range1距離相等
};

class card
{
public:
	card();
	card(int number, int dex, vector<skill> above, vector<skill> below);
	~card();

	int number = 0;//編號
	int dex = 0;//敏捷
	vector<skill> skill_above;
	vector<skill> skill_below;

	bool discard = false;//true為棄牌 false為手牌
	bool remove = false;//true為從棄牌堆中移除的一張牌 false則不是
	bool up = true;//true為up false為down
};
