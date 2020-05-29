#pragma once
#include<iostream>
#include"evil_guy.h"
#include"monster_card.h"
//此為怪物的資訊
//////////////////////////////////////////////////////////////////////////////////////////////////////

class evil_guy {
private:
	string monster_name;
	int monster_hp;//
	int monster_attack;//怪物的攻擊值
	int monster_sheild;//護甲
	int range;//怪物的射程
	int x;//x跟y為怪物的位置
	int y;
	vector<monster_card>card;
public:
	
};
