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
	int range = 0;//��attack�~��range range0�Prange1�Z���۵�
};

class card
{
public:
	card();
	card(int number, int dex, vector<skill> above, vector<skill> below);
	~card();

	int number = 0;//�s��
	int dex = 0;//�ӱ�
	vector<skill> skill_above;
	vector<skill> skill_below;

	bool discard = false;//true����P false����P
	bool remove = false;//true���q��P�襤�������@�i�P false�h���O
	bool up = true;//true��up false��down
};
