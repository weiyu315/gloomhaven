#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"character.h"
#include"monster.h"
#include"map.h"
#include"evil_guy.h"


using namespace std;

int main(int argc, char* argv[])
{
	int caracter_qualite;
	string play_or_exit;
	cin >> play_or_exit;
	if (play_or_exit == "play")
	{
		cout << "�п�J�X������ƶq";
		cin >> caracter_qualite;
		for (int i = 0; i < caracter_qualite; i++) {

		}

		monster a("monster1.txt");
		map b("map1.txt");


		//����B�Ǫ��ɮ׶}��
		/*int debug_Mode;
		ifstream character_InFile(argv[1], ios::in), monster_InFile(argv[2], ios::in);
		debug_Mode = atoi(argv[3]);*/
		

	}
	
	return 0;
}
