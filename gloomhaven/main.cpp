#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"character.h"
#include"monster.h"

using namespace std;

int main(int argc, char* argv[])
{
	
	string play_or_exit;
	cin >> play_or_exit;
	if (play_or_exit == "play")
	{
		string temporarily_monster = "monster1.txt";//暫時的怪獸讀檔資料
		monster a(temporarily_monster);
		//角色、怪物檔案開啟
		/*int debug_Mode;
		ifstream character_InFile(argv[1], ios::in), monster_InFile(argv[2], ios::in);
		debug_Mode = atoi(argv[3]);
		int character_amount;
		vector<character> cha;
		cha.resize(character_amount);
		character_InFile >> character_amount;
		string input;
		
		int characterAmount;
		cin >> characterAmount;*/

	}
	
	return 0;
}
