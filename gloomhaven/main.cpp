#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"character.h"
#include"monster.h"
#include"map.h"
#include"evil_guy.h"


using namespace std;

void characterFileReader(string fileName, vector<character> Character);
int main(int argc, char* argv[])
{
	vector<character> Character;
	int character_qualite;
	string play_or_exit, map_file;
	string play_or_exit;
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
				re_Monster.initialization_bad_guy(b.Get_monster_name(i), b.Get_monster_location_x(i), b.Get_monster_location_y(i), b.Get_monster_status(i, character_qualite), a);
				re_Monster.text();
				Monster.push_back(re_Monster);
			}

		monster a("monster1.txt");

		//����B�Ǫ��ɮ׶}��
		int debug_Mode;
		ifstream character_inFile(argv[1], ios::in), monster_inFile(argv[2], ios::in);
		debug_Mode = atoi(argv[3]);
		
	}
	
	return 0;
}
void characterFileReader(string fileName, vector<character> Character)
{
	ifstream inFile(fileName, ios::in);
	int character_amount;
	inFile >> character_amount;//��Ʈw����ƶq
	for (int i = 0; i < character_amount; i++)//Ū��������
	{
		character newCharacter;
		inFile >> newCharacter.name >> newCharacter.max_hp >> newCharacter.hand_card_amount;
		inFile >> newCharacter.total_card_amount;
		int card_number;
		inFile >> card_number;
		for (int j = 0; j < newCharacter.total_card_amount; j++)//Ū�����⪺�C�i�d��
		{
			card newCard;
			newCard.number = card_number;
			inFile >> newCard.dex;
			string newSkill_name;
			int newVal;
			bool above = true;
			while (inFile >> newSkill_name)//Ū���C�i�d������skill
			{
				if ("0" <= newSkill_name && newSkill_name <= "9")//��Ū����U�i�d����number�ɰ���Ū��
				{
					card_number = stoi(newSkill_name);
					break;
				}
				skill newSkill;
				inFile >> newVal;
				newSkill.set_skill(newSkill_name, newVal);
				if (newSkill_name == "-")//��Ū����Ÿ��ɡ@�Nabove�ରbelow�ð���ǤJ��ƨ�card class
				{
					above = false;
					continue;
				}
				if (above)
				{
					newCard.skill_above.push_back(newSkill);
				}
				else
				{
					newCard.skill_below.push_back(newSkill);
				}
			}
			newCharacter.total_card.push_back(newCard);
		}
		Character.push_back(newCharacter);
	}
	inFile.close();
}