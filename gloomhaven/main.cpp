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
	int character_qualite;
	string play_or_exit,map_file;
	cin >> play_or_exit;
	if (play_or_exit == "play")
	{
		monster a("monster1.txt");
		cout << "�п�J�X������ƶq\n";
		cin >> character_qualite;
		for (int i = 0; i < character_qualite; i++) {

		}
		cin >> map_file;
		map b(map_file);
		vector<evil_guy> Monster;//�Ǫ�
		evil_guy  re_Monster;//�x�s�n��ivector���Ǫ�
		for (int i = 0; i < b.Get_monster_quaility(); i++) {
			if (b.Get_monster_status(i, character_qualite) == 1 || b.Get_monster_status(i, character_qualite) == 2) {
			re_Monster.initialization_bad_guy(b.Get_monster_name(i) , b.Get_monster_location_x(i),b.Get_monster_location_y(i),b.Get_monster_status(i, character_qualite),a);
				re_Monster.text();
				Monster.push_back(re_Monster);
			}
		}
		


		//����B�Ǫ��ɮ׶}��
		/*int debug_Mode;
		ifstream character_InFile(argv[1], ios::in), monster_InFile(argv[2], ios::in);
		debug_Mode = atoi(argv[3]);*/
		

	}
	
	return 0;
}
