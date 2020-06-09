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
		cout << "�п�J�X������ƶq:";
		string map_file;
		int debug_Mode=1;
		characterFileReader("character1.txt", Character);
		/*characterFileReader(argv[1], Character);//����Ū��
		ifstream monster_inFile(argv[2], ios::in);
		debug_Mode = atoi(argv[3]);
		/*------------------------------------Ū���W��������------------------------------------*/
		vector<character> playCharacter;//�W��������
		int playCharacter_amount;
		cin >> playCharacter_amount;
		for (int i = 0; i < playCharacter_amount; i++)
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
		}
		char mapName = 'A';
		for (auto& n : playCharacter)
		{
			n.map_name = mapName;
			mapName++;
		}
		/*--------------------------------------Ū���a���ɮ�--------------------------------------*/
		monster a("monster1.txt");//�Ȯ�
		cin >> map_file;
		map Map(map_file);
		vector<evil_guy> Monster;//�Ҧ��Ǫ�
		vector<evil_guy> output_Monster;//�i��ܪ��Ǫ�
		evil_guy  re_Monster;//�x�s�n��ivector���Ǫ�
		for (int i = 0; i < Map.Get_monster_quaility(); i++) {
			if (Map.Get_monster_status(i, playCharacter_amount) == 1 || Map.Get_monster_status(i, playCharacter_amount) == 2) {
				re_Monster.initialization_bad_guy(Map.Get_monster_name(i), Map.Get_monster_char_name(i), Map.Get_monster_location_x(i), Map.Get_monster_location_y(i), Map.Get_monster_status(i, playCharacter_amount), a);
				Monster.push_back(re_Monster);
			}
		}
		/*---------------------------------------��ܦa��-----------------------------------------*/
		for (int i = 0; i < playCharacter_amount; i++) {
			Map.Set_initialization_point();
			Map.output_decide_map(Monster);
			Map.Set_start_point();
		}
		Map.output(Monster);
		/*-----------------------------------------�^�X-------------------------------------------*/
		int round = 0;
		bool end_round = false;
		int using_card_number;
		string first_input, action;
		while (!end_round)
		{
			cout << "round " << ++round << ":" << endl;
			/*-----------------------------------�����ܵP���ǩάO����άOcheck---------------------------------------*/
			for (int i = 0; i < playCharacter.size(); i++)
			{
				cin >> first_input >> action;
				int k = 0;
				bool map_name = true;
				for (; k < playCharacter.size(); k++)
				{
					if (playCharacter[k].map_name == first_input)
					{
						map_name = true;
						break;
					}
					map_name = false;
				}
				if (map_name)//�Ĥ@�ӿ�J������N��ABC
				{
					if (action == "-1")
					{
						if (playCharacter[k].discard_card.size() < 2)
						{
							cout << "error move!!!" << endl;
						}
						else
						{
							playCharacter[k].round_dex = 99;
							playCharacter[k].long_rest = true;
						}
					}
					else if (action == "check")
					{
						cout << "hand: ";
						for (auto n : playCharacter[k].hand_card)
						{
							cout << n.number;
							if (n.number != playCharacter[k].hand_card[playCharacter[k].hand_card.size() - 1].number)
							{
								cout << ", ";
							}
							else
							{
								cout << "; discard: ";
							}
						}
						for (auto m : playCharacter[k].discard_card)
						{
							cout << m.number;
							if (m.number != playCharacter[k].discard_card[playCharacter[k].discard_card.size() - 1].number)
							{
								cout << ", ";
							}
						}
						cout << endl;
						i--;//��i���|�W�[
					}
					else
					{
						using_card_number = stoi(action);
						for (int j = 0; j < 2; j++)
						{
							playCharacter[k].setUsing_card(j, using_card_number, playCharacter[k].using_card, playCharacter[k].hand_card);
							if (j != 1)
							{
								cin >> using_card_number;
							}
						}

						playCharacter[k].round_dex = playCharacter[k].using_card[0].dex;//�H�Ĥ@�i�P���ӱ��ȧ@�������ӱ���
					}
				}
				else//�Ĥ@�ӿ�J���O����N��
				{

				}
			}
			/*-----------------------------------------4-1�Ǫ���P-------------------------------------------*/\
				output_Monster.clear();
				for (int i = 0; i < Monster.size(); i++) {
					if (Map.monster_decide(Monster[i].Get_x(), Monster[i].Get_y()) == 1) {
						output_Monster.push_back(Monster[i]);
					}
			}
				
			for (int i = 0; i < output_Monster.size(); i++) {
				bool des;
				des = false;
				for (int j = 0; j < i; j++) {
					if ( output_Monster[i].Get_monster_name()==output_Monster[j].Get_monster_name()) {
							output_Monster[i].Set_correct_card(output_Monster[j].Get_correct_card());
							des = true;
						}
				}
				if (des == false) {
					output_Monster[i].choise_action(debug_Mode);
				}
			}
			/*-----------------------------------------4-2���ǧP�_-------------------------------------------*/
			int ro = playCharacter.size() + output_Monster.size();
			for (int i = 0; i < playCharacter.size(); i++) {
				playCharacter[i].round_order = i;
			}
			for (int i = 0; i < output_Monster.size(); i++) {
				output_Monster[i].round_order = i+ playCharacter.size();
			}
				for (int i = 0; i < ro; i++) {
					for (int j = 0; j < playCharacter.size(); j++) {
						if (playCharacter[j].round_order == i) {
								cout << playCharacter[j].map_name << " ";
								if (0 <= playCharacter[j].round_dex && playCharacter[j].round_dex <= 9)
								{
									cout << "0" << playCharacter[j].round_dex << " ";
								}
								else
								{
									cout << playCharacter[j].round_dex << " ";
								}
								for (int x = 0; x < 2; x++)
								{
									cout << playCharacter[j].using_card[x].number;
									if (x == 0)
									{
										cout << " ";
									}
									else
									{
										cout << endl;
									}
						}
					}
				}
					for (int j = 0; j < output_Monster.size(); j++) {
						if (output_Monster[j].round_order == i) {
							output_Monster[j].output();
						}
					}
			}
			/*-----------------------------------------�P�_�Ǫ��O�_�ӧQ-------------------------------------------*/
			/*for (auto n : playCharacter)
			{
				if (n.round_hp > 0)
				{
					end_round = false;
					goto end_for_loop;
				}
				end_round = true;
			}
			if (end_round)
			{
				cout << "monster win~" << endl;
				break;
			}*/
			/*-----------------------------------------�P�_����O�_�ӧQ-------------------------------------------*/
		/*end_for_loop:;*/

		}
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
		newCharacter.round_hp = newCharacter.max_hp;
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

/*------------------------------------character��Ʈw��X-------------------------------------*/
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
		cout << "�п�J�X������ƶq:";
		string map_file;
		int debug_Mode = 1;//�Ȯɵ���1
		characterFileReader("character1.txt", Character);
		/*characterFileReader(argv[1], Character);//����Ū��
		ifstream monster_inFile(argv[2], ios::in);
		debug_Mode = atoi(argv[3]);
		/*------------------------------------Ū���W��������------------------------------------*/
		vector<character> playCharacter;//�W��������
		int playCharacter_amount;
		cin >> playCharacter_amount;
		for (int i = 0; i < playCharacter_amount; i++)
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
		}
		char mapName = 'A';
		for (auto& n : playCharacter)
		{
			n.map_name = mapName;
			mapName++;
		}
		/*--------------------------------------Ū���a���ɮ�--------------------------------------*/
		monster a("monster1.txt");//�Ȯ�
		cin >> map_file;
		map Map(map_file);
		vector<evil_guy> Monster;//�Ǫ�
		evil_guy  re_Monster;//�x�s�n��ivector���Ǫ�
		for (int i = 0; i < Map.Get_monster_quaility(); i++) {
			if (Map.Get_monster_status(i, playCharacter_amount) == 1 || Map.Get_monster_status(i, playCharacter_amount) == 2) {
				re_Monster.initialization_bad_guy(Map.Get_monster_name(i), Map.Get_monster_char_name(i), Map.Get_monster_location_x(i), Map.Get_monster_location_y(i), Map.Get_monster_status(i, playCharacter_amount), a);
				Monster.push_back(re_Monster);
			}
		}
		/*---------------------------------------��ܦa��-----------------------------------------*/
		for (int i = 0; i < playCharacter_amount; i++) {
			Map.Set_initialization_point();
			Map.output_decide_map(Monster);
			Map.Set_start_point();
		}
		Map.output(Monster);
		/*-----------------------------------------�^�X-------------------------------------------*/
		int round = 0;
		bool end_round = false;
		int using_card_number;
		string first_input, action;
		cout << "round " << ++round << ":" << endl;
		bool map_name_finish = false;
		while (!end_round)
		{
			/*-----------------------------------�����ܵP���ǩάO����άOcheck---------------------------------------*/
			for (auto n : playCharacter)
			{
				n.choose_using_card = false;
				n.long_rest = false;
			}
			while(true)
			{
				for (auto n : playCharacter)
				{
					if (n.long_rest || n.choose_using_card)
					{
						map_name_finish = true;
						continue;
					}
					map_name_finish = false;
				}
				int k = 0;
				bool map_name = true;
				if (map_name_finish)
				{
					break;
				}
				cin >> first_input;
				for (; k < playCharacter.size(); k++)
				{
					if (playCharacter[k].map_name == first_input)
					{
						map_name = true;
						break;
					}
					map_name = false;
				}
				if (map_name)//�Ĥ@�ӿ�J������N��ABC
				{
					if (playCharacter[k].alive)
					{
						cin >> action;
						if (action == "-1")
						{
							if (playCharacter[k].discard_card.size() < 2)
							{
								cout << "Your discard amount is lower than 2, so you can't use long rest." << endl;
							}
							else
							{
								playCharacter[k].round_dex = 99;
								playCharacter[k].long_rest = true;
							}
						}
						else if (action == "check")
						{
							cout << "hand: ";
							for (auto n : playCharacter[k].hand_card)
							{
								cout << n.number;
								if (n.number != playCharacter[k].hand_card[playCharacter[k].hand_card.size() - 1].number)
								{
									cout << ", ";
								}
								else
								{
									cout << "; discard: ";
								}
							}
							for (auto m : playCharacter[k].discard_card)
							{
								cout << m.number;
								if (m.number != playCharacter[k].discard_card[playCharacter[k].discard_card.size() - 1].number)
								{
									cout << ", ";
								}
							}
							cout << endl;
						}
						else
						{
							playCharacter[k].choose_using_card = true;
							using_card_number = stoi(action);
							for (int j = 0; j < 2; j++)
							{
								playCharacter[k].setUsing_card(j, using_card_number, playCharacter[k].using_card, playCharacter[k].hand_card);
								if (j != 1)
								{
									cin >> using_card_number;
								}
							}
							playCharacter[k].round_dex = playCharacter[k].using_card[0].dex;//�H�Ĥ@�i�P���ӱ��ȧ@�������ӱ���

						}
					}
					else
					{
						cout << playCharacter[k].map_name << " is killed!!" << endl;
					}
				}
			}
			for (auto n : playCharacter)
			{
				if (n.alive && !n.long_rest)
				{
					cout << n.map_name << " ";
					if (0 <= n.round_dex && n.round_dex <= 9)
					{
						cout << "0" << n.round_dex << " ";
					}
					else
					{
						cout << n.round_dex << " ";
					}
					for (int x = 0; x < 2; x++)
					{
						cout << n.using_card[x].number;
						if (x == 0)
						{
							cout << " ";
						}
						else
						{
							cout << endl;
						}
					}
				}
			}
			string next_input;
			for (auto& n : playCharacter)//�C�����⪺�C���ʧ@
			{
				int card_numberTmp;//�s5u 12d�������e�����Ʀr
				char up_or_down;//�su��d
				if (n.alive && !n.long_rest)
				{
					cout << n.map_name << "'s turn: card " << n.using_card[0].number << " " << n.using_card[1].number << endl;
					cin >> next_input;
					up_or_down = next_input[next_input.size() - 1];
					next_input.pop_back();
					card_numberTmp = stoi(next_input);

				}
			}
			/*-----------------------------------------�Ǫ���P-------------------------------------------*/
			for (int i = 0; i < Monster.size(); i++) {
				if (Map.monster_decide(Monster[i].Get_x(), Monster[i].Get_y()) == 1) {
					Monster[i].choise_action(debug_Mode);
				}
			}
			cout << "round " << ++round << ":" << endl;
		}
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
		newCharacter.round_hp = newCharacter.max_hp;
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
////////////////////
//////////////////
