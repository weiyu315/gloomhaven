#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include"character.h"
#include"monster.h"
#include"map.h"
#include"evil_guy.h"

using namespace std;

void characterFileReader(string fileName, vector<character>& Character);
/*-------------------------------main-------------------------------*/
int main(int argc, char* argv[])
{
	vector<character> Character;//�����Ʈw
	string play_or_exit;
	cin >> play_or_exit;
	if (play_or_exit == "play")
	{
		string map_file;
		int debug_Mode;
		/*characterFileReader(argv[1], Character);//����Ū��
		ifstream monster_inFile(argv[2], ios::in);
		debug_Mode = atoi(argv[3]);
		/*-------------------------------Ū���W��������-------------------------------*/
		vector<character> playCharacter;//�W��������
		int playCharacter_amount;
		cin >> playCharacter_amount;
		/*for (int i = 0; i < playCharacter_amount; i++)
		{
			string playCharacter_name;
			cin >> playCharacter_name;
			int index = 0;
			while (Character[index].name != playCharacter_name)
			{
				index++;
			}
			playCharacter.push_back(Character[index]);
			for (int j = 0; j < Character[index].hand_card_amount; j++)//��ܤ�P
			{
				int card_number;
				cin >> card_number;
				int x = 0;
				while (playCharacter[playCharacter.size() - 1].total_card[x].number != card_number)
				{
					x++;
				}
				playCharacter[playCharacter.size() - 1].hand_card.push_back(playCharacter[playCharacter.size() - 1].total_card[x]);
			}
		}*/
		/*-------------------------------Ū���W��������-------------------------------*/
		/*---------------------------------Ū���a���ɮ�---------------------------------*/
		monster a("monster1.txt");//�Ȯ�
		cin >> map_file;
		map Map(map_file);
		vector<evil_guy> Monster;//�Ǫ�
		evil_guy  re_Monster;//�x�s�n��ivector���Ǫ�
		for (int i = 0; i < Map.Get_monster_quaility(); i++) {
			if (Map.Get_monster_status(i, playCharacter_amount) == 1 || Map.Get_monster_status(i, playCharacter_amount) == 2) {
				re_Monster.initialization_bad_guy(Map.Get_monster_name(i),Map.Get_monster_char_name(i), Map.Get_monster_location_x(i), Map.Get_monster_location_y(i), Map.Get_monster_status(i, playCharacter_amount), a);
				Monster.push_back(re_Monster);
			}
			/*---------------------------------Ū���a���ɮ�---------------------------------*/
		}
		/*-------------------------------------��ܦa��----------------------------------------*/
		Map.output_decide_map(Monster);
		/*-------------------------------------��ܦa��----------------------------------------*/

		return 0;
	}
}
	void characterFileReader(string fileName, vector<character>& Character)
	{
		ifstream inFile(fileName, ios::in);
		int character_amount;
		inFile >> character_amount;//��Ʈw����ƶq
		for (int i = 0; i < character_amount; i++)//Ū��������
		{
			character newCharacter;
			inFile >> newCharacter.name >> newCharacter.max_hp >> newCharacter.hand_card_amount;
			inFile >> newCharacter.total_card_amount;
			inFile.ignore();
			for (int j = 0; j < newCharacter.total_card_amount; j++)//Ū�����⪺�C�i�d��
			{
				card newCard;
				string card_line;
				getline(inFile, card_line);
				stringstream ss(card_line);
				ss >> newCard.number >> newCard.dex;
				string newSkill_name;
				int newVal;
				bool above = true;
				while (ss >> newSkill_name)
				{
					skill newSkill;
					if (newSkill_name == "-")
					{
						above = false;
						continue;
					}
					ss >> newVal;
					if (newSkill_name == "range")
					{
						if (above)
						{
							newCard.skill_above[newCard.skill_above.size() - 1].range = newVal;
						}
						else
						{
							newCard.skill_below[newCard.skill_below.size() - 1].range = newVal;
						}
						continue;
					}
					newSkill.set_skill(newSkill_name, newVal);
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

	/*-------------------------------character��Ʈw��X-------------------------------*/
			//characterFileReader("character1.txt", Character);
			//for (int i = 0; i < Character.size(); i++)
			//{
			//	cout << Character[i].name << " " << Character[i].max_hp << " " << Character[i].hand_card_amount << endl;
			//	for (int j = 0; j < Character[i].total_card_amount; j++)
			//	{
			//		cout << Character[i].total_card[j].number << " " << Character[i].total_card[j].dex << " ";
			//		for (int m = 0; m < Character[i].total_card[j].skill_above.size(); m++)
			//		{
			//			cout << Character[i].total_card[j].skill_above[m].type << " " << Character[i].total_card[j].skill_above[m].value << " ";
			//		}
			//		cout << "- ";
			//		for (int n = 0; n < Character[i].total_card[j].skill_below.size(); n++)
			//		{
			//			cout << Character[i].total_card[j].skill_below[n].type << " " << Character[i].total_card[j].skill_below[n].value << " ";
			//		}
			//		cout << endl;
			//	}
			//}