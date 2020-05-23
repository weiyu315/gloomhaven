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
		//角色、怪物檔案開啟
		int debug_Mode;
		ifstream character_InFile(argv[1], ios::in), monster_InFile(argv[2], ios::in);
		debug_Mode = atoi(argv[3]);
		

	}
	
	return 0;
}
