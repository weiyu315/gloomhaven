#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"character.h"
#include"monster.h"

using namespace std;

void characterFileReader(string fileName, vector<character> Character);
int main(int argc, char* argv[])
{
	vector<character> Character;
	string play_or_exit;
	cin >> play_or_exit;
	if (play_or_exit == "play")
	{
		//角色、怪物檔案開啟
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
	inFile >> character_amount;//資料庫角色數量
	for (int i = 0; i < character_amount; i++)//讀取角色資料
	{
		character newCharacter;
		inFile >> newCharacter.name >> newCharacter.max_hp >> newCharacter.hand_card_amount;
		inFile >> newCharacter.total_card_amount;
		int card_number;
		inFile >> card_number;
		for (int j = 0; j < newCharacter.total_card_amount; j++)//讀取角色的每張卡片
		{
			card newCard;
			newCard.number = card_number;
			inFile >> newCard.dex;
			string newSkill_name;
			int newVal;
			bool above = true;
			while (inFile >> newSkill_name)//讀取每張卡片中的skill
			{
				if ("0" <= newSkill_name && newSkill_name <= "9")//當讀取到下張卡片的number時停止讀取
				{
					card_number = stoi(newSkill_name);
					break;
				}
				skill newSkill;
				inFile >> newVal;
				newSkill.set_skill(newSkill_name, newVal);
				if (newSkill_name == "-")//當讀取到符號時　將above轉為below並停止傳入資料到card class
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