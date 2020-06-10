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
	vector<character> Character;//角色資料庫
	string play_or_exit;
	cin >> play_or_exit;
	if (play_or_exit == "play")
	{
		cout << "請輸入出場角色數量:";
		string map_file;
		int debug_Mode = 0;//暫時等於1
		characterFileReader("character1.txt", Character);
		/*characterFileReader(argv[1], Character);//角色讀檔
		ifstream monster_inFile(argv[2], ios::in);
		debug_Mode = atoi(argv[3]);
		/*------------------------------------讀取上場角色資料------------------------------------*/
		vector<character> playCharacter;//上場的角色
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
			for (int j = 0; j < Character[index].hand_card_amount; j++)//選擇手牌
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
		/*--------------------------------------讀取地圖檔案--------------------------------------*/
		monster a("monster1.txt");//暫時
		cin >> map_file;
		map Map(map_file);
		vector<evil_guy> Monster;//怪物
		vector<evil_guy> output_Monster;//存放怪物
		evil_guy  re_Monster;//儲存要放進vector的怪物
		for (int i = 0; i < Map.Get_monster_quaility(); i++) {
			if (Map.Get_monster_status(i, playCharacter_amount) == 1 || Map.Get_monster_status(i, playCharacter_amount) == 2) {
				re_Monster.initialization_bad_guy(Map.Get_monster_name(i), Map.Get_monster_char_name(i), Map.Get_monster_location_x(i), Map.Get_monster_location_y(i), Map.Get_monster_status(i, playCharacter_amount), a);
				Monster.push_back(re_Monster);
				Monster[Monster.size() - 1].live_or_die = 1;
			}
		}
		/*---------------------------------------顯示地圖-----------------------------------------*/
		for (int i = 0; i < playCharacter_amount; i++) {
			Map.Set_initialization_point();
			Map.output_decide_map(Monster);
			Map.Set_start_point();
		}
		Map.output(Monster);
		/*-----------------------------------------回合-------------------------------------------*/
		int round = 0;
		bool end_round = false;
		int using_card_number;
		string first_input, action;
		cout << "round " << ++round << ":" << endl;
		bool map_name_finish = false;
		while (!end_round)
		{
			/*-----------------------------------角色選擇牌順序或是長休或是check---------------------------------------*/
			for (auto n : playCharacter)
			{
				n.choose_using_card = false;
				n.long_rest = false;
				n.round_shield = 0;
			}
			int playCharacter_amount = playCharacter.size();
			while(true)
			{
				if (playCharacter_amount <= 0) { break; }
				int k = 0;
				bool map_name = true;
				if (map_name_finish)
				{
					break;
				}
			re_input:;
				cin >> first_input;
				for (; k < playCharacter.size(); k++)
				{
					if (playCharacter[k].map_name == first_input[0])
					{
						map_name = true;
						break;
					}
					map_name = false;
				}
				if (map_name)//第一個輸入為角色代號ABC
				{
					if (playCharacter[k].alive)
					{
						cin >> action;
						if (action == "-1")
						{
							if (playCharacter[k].discard_card_amount < 2)
							{
								cout << "Your discard amount is lower than 2, so you can't use long rest." << endl;
							}
							else
							{
								playCharacter[k].round_dex = 99;
								playCharacter[k].long_rest = true;
								playCharacter_amount--;
							}
						}
						else if (action == "check")
						{
							card tmp;
							for (int z = 0; z < playCharacter[k].hand_card.size(); z++)
							{
								for (int y = z + 1; y < playCharacter[k].hand_card.size(); y++)
								{
									if (playCharacter[k].hand_card[z].number > playCharacter[k].hand_card[y].number)
									{
										tmp = playCharacter[k].hand_card[z];
										playCharacter[k].hand_card[z] = playCharacter[k].hand_card[y];
										playCharacter[k].hand_card[y] = tmp;
									}
								}
							}
							cout << "hand: ";
							for (auto n : playCharacter[k].hand_card)
							{
								if (!n.discard && !n.remove)
								{
									cout << n.number;
									if (n.number != playCharacter[k].hand_card[playCharacter[k].hand_card.size() - 1].number)
									{
										cout << ", ";
									}
								}
							}
							cout << "; discard: ";
							int amountTmp = 0;
							for (int m = 0; m < playCharacter[k].hand_card.size(); m++)
							{
								if (playCharacter[k].hand_card[m].discard && !playCharacter[k].hand_card[m].remove)
								{
									cout << playCharacter[k].hand_card[m].number;
									amountTmp++;
									if (amountTmp < playCharacter[k].discard_card_amount)
									{
										cout << ", ";
									}
								}
							}
							cout << endl;
						}
						else
						{
							playCharacter[k].choose_using_card = true;
							using_card_number = stoi(action);
							bool using_card_number_exist = true;
							for (int j = 0; j < 2; j++)
							{
								using_card_number_exist = playCharacter[k].setUsing_card(j, using_card_number, playCharacter[k].using_card, playCharacter[k].hand_card);
								if (j != 1)
								{
									cin >> using_card_number;
								}
								if (!using_card_number_exist)
								{
									goto re_input;
									cout << "123" << endl;
								}
							}
							playCharacter_amount--; 
							playCharacter[k].round_dex = playCharacter[k].using_card[0].dex;//以第一張牌的敏捷值作為本輪敏捷值
							
						}
					}
					else
					{
						cout << playCharacter[k].map_name << " is killed!!" << endl;
					}
				}
			}
			/*-----------------------------------------怪物選牌-------------------------------------------*/
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
					if (output_Monster[i].Get_monster_name() == output_Monster[j].Get_monster_name()) {
						output_Monster[i].Set_correct_card(output_Monster[j].Get_correct_card());
						des = true;
					}
				}
				if (des == false) {
					output_Monster[i].choise_action(debug_Mode);
				}
			}
			/*-----------------------------------------4-2順序出牌-------------------------------------------*/
			int ro = playCharacter.size() + output_Monster.size();
			for (int i = 0; i < playCharacter.size(); i++) {
				playCharacter[i].round_order = i;
			}
			for (int i = 0; i < output_Monster.size(); i++) {
				output_Monster[i].round_order = i + playCharacter.size();
			}
			int c;
			for (int i = 0; i < playCharacter.size(); i++) {
				for (int j = 0; j < i; j++) {
					if (playCharacter[i].round_dex < playCharacter[j].round_dex && playCharacter[i].round_order > playCharacter[j].round_order) {
						c = playCharacter[i].round_order;
						playCharacter[i].round_order = playCharacter[j].round_order;
						playCharacter[j].round_order = c;
					}
					if (playCharacter[i].round_dex > playCharacter[j].round_dex && playCharacter[i].round_order < playCharacter[j].round_order) {
						c = playCharacter[i].round_order;
						playCharacter[i].round_order = playCharacter[j].round_order;
						playCharacter[j].round_order = c;
					}
					if (playCharacter[i].round_dex == playCharacter[j].round_dex) {
						if (playCharacter[i].map_name < playCharacter[j].map_name && playCharacter[i].round_order > playCharacter[j].round_order) {
							c = playCharacter[i].round_order;
							playCharacter[i].round_order = playCharacter[j].round_order;
							playCharacter[j].round_order = c;
						}
						if (playCharacter[i].map_name > playCharacter[j].map_name&& playCharacter[i].round_order < playCharacter[j].round_order) {
							c = playCharacter[i].round_order;
							playCharacter[i].round_order = playCharacter[j].round_order;
							playCharacter[j].round_order = c;
						}
					}
				}
			}
			for (int i = 0; i < output_Monster.size(); i++) {
				for (int j = 0; j < i; j++) {
					if (output_Monster[i].Get_correct_card_agility() < output_Monster[j].Get_correct_card_agility() && output_Monster[i].round_order > output_Monster[j].round_order) {
						c = output_Monster[i].round_order;
						output_Monster[i].round_order = output_Monster[j].round_order;
						output_Monster[j].round_order = c;
					}
					if (output_Monster[i].Get_correct_card_agility() > output_Monster[j].Get_correct_card_agility() && output_Monster[i].round_order < output_Monster[j].round_order) {
						c = output_Monster[i].round_order;
						output_Monster[i].round_order = output_Monster[j].round_order;
						output_Monster[j].round_order = c;
					}
					if (output_Monster[i].Get_correct_card_agility() == output_Monster[j].Get_correct_card_agility()) {
						if (output_Monster[i].Get_monster_card_name() < output_Monster[j].Get_monster_card_name() && output_Monster[i].round_order > output_Monster[j].round_order) {
							c = output_Monster[i].round_order;
							output_Monster[i].round_order = output_Monster[j].round_order;
							output_Monster[j].round_order = c;
						}
						if (output_Monster[i].Get_monster_card_name() > output_Monster[j].Get_monster_card_name() && output_Monster[i].round_order < output_Monster[j].round_order) {
							c = output_Monster[i].round_order;
							output_Monster[i].round_order = output_Monster[j].round_order;
							output_Monster[j].round_order = c;
						}
					}
				}
			}
			for (int i = 0; i < playCharacter.size(); i++) {
				for (int j = 0; j < output_Monster.size(); j++) {
					if (playCharacter[i].round_dex < output_Monster[j].Get_correct_card_agility() && playCharacter[i].round_order > output_Monster[j].round_order) {
						c = playCharacter[i].round_order;
						playCharacter[i].round_order = output_Monster[j].round_order;
						output_Monster[j].round_order = c;
					}
					if (playCharacter[i].round_dex > output_Monster[j].Get_correct_card_agility() && playCharacter[i].round_order < output_Monster[j].round_order) {
						c = playCharacter[i].round_order;
						playCharacter[i].round_order = output_Monster[j].round_order;
						output_Monster[j].round_order = c;
					}
				}
			}
			for (int i = 0; i < ro; i++) {
				for (int j = 0; j < playCharacter.size(); j++) {
					if (playCharacter[j].round_order == i && playCharacter[j].alive) {
						cout << playCharacter[j].map_name << " ";
						if (0 <= playCharacter[j].round_dex && playCharacter[j].round_dex <= 9)
						{
							cout << "0" << playCharacter[j].round_dex << " ";
						}
						else
						{
							cout << playCharacter[j].round_dex << " ";
						}
						if (!playCharacter[j].long_rest)
						{
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
						else
						{
							cout << "-1" << endl;
						}
					}
				}
				for (int j = 0; j < output_Monster.size(); j++) {
					bool des;
					if (output_Monster[j].round_order == i) {
						des = false;
						for (int k = 0; k < j; k++) {
							if (output_Monster[k].Get_monster_name() == output_Monster[j].Get_monster_name()) {
								des = true;
							}
						}
						if (des == false) {
							output_Monster[j].output();
						}
					}
				}
			}
			/*-----------------------------------------4-3戰鬥出牌-------------------------------------------*/
			for (int i = 0; i < playCharacter.size() + output_Monster.size(); i++) {
				string next_input;
				for (int j = 0; j < playCharacter.size(); j++) {
					if (playCharacter[j].round_order == i) {
						int card_numberTmp;//存5u 12d之類的前面的數字 或是 在長休狀態下要丟棄的牌
						char up_or_down;//存u或d
						if (playCharacter[j].alive && !playCharacter[j].long_rest && playCharacter[j].choose_using_card)//若角色活著且非長休狀態
						{
							cout << playCharacter[j].map_name << "'s turn: card " << playCharacter[j].using_card[0].number << " " << playCharacter[j].using_card[1].number << endl;
						restart:;
							cin >> next_input;//輸入3d
							if (next_input == "check")
							{
								character character_tmp;
								for (int i = 0; i < playCharacter.size(); i++)
								{
									for (int j = i + 1; j < playCharacter.size(); j++)
									{
										if (playCharacter[i].map_name > playCharacter[j].map_name)
										{
											character_tmp = playCharacter[i];
											playCharacter[i] = playCharacter[j];
											playCharacter[j] = character_tmp;
										}
									}
								}
								for (auto n : playCharacter)
								{
									if (n.alive)
									{
										cout << n.map_name << "-hp: " << n.round_hp << ", shield: " << n.round_shield << endl;
									}
								}
								goto restart;
							}
							else
							{
								up_or_down = next_input[next_input.size() - 1];//存d
								next_input.pop_back();//刪除d
								card_numberTmp = stoi(next_input);//存3
								if (playCharacter[j].using_card[0].number != card_numberTmp)//將牌照出牌順序排列
								{
									card tmp;
									tmp = playCharacter[j].using_card[0];
									playCharacter[j].using_card[0] = playCharacter[j].using_card[1];
									playCharacter[j].using_card[1] = tmp;
								}

								if (up_or_down == 'u')
								{
									playCharacter[j].using_card[0].up = true;
									playCharacter[j].using_card[1].up = false;
								}
								else if (up_or_down == 'd')
								{
									playCharacter[j].using_card[0].up = false;
									playCharacter[j].using_card[1].up = true;
								}
								else
								{
									cout << "error input!!!" << endl;
									goto restart;
								}
								char monster_map_name;
								for (auto m : playCharacter[j].using_card)
								{
									if (m.up)
									{
										for (auto s : m.skill_above)
										{
											switch (s.type)
											{
											case 0://attack val
											start_u:;
												cout << "attack monster: ";
												cin >> monster_map_name;
												if (monster_map_name != '0')
												{
													if ('a' <= monster_map_name && monster_map_name <= 'z')
													{
														if (Map.distant(playCharacter[j].map_name, monster_map_name, s.range))//判斷攻擊距離是否足夠
														{
															int b = 0;
															bool find_monster = true;
															for (; b < Monster.size(); b++)
															{
																if (Monster[b].Get_monster_card_name() == monster_map_name)
																{
																	find_monster = true;
																	break;
																}
																find_monster = false;
															}
															if (find_monster)
															{
																int damage;
																if (s.value >= Monster[b].monster_current_shield)
																{
																	damage = s.value - Monster[b].monster_current_shield;
																}
																else
																{
																	damage = 0;
																}
																Monster[b].monster_current_hp -= damage;
																if (Monster[b].monster_current_hp <= 0) {
																	Monster[b].live_or_die = false;
																}
																Map.output(Monster);
																cout << playCharacter[j].map_name << " attack " << Monster[b].Get_monster_card_name() << " " << damage << " damage, " << Monster[b].Get_monster_card_name() << " shield " << Monster[b].monster_current_shield << ", " << Monster[b].Get_monster_card_name() << " remain " << Monster[b].monster_current_hp << " hp" << endl;
																if (!Monster[b].live_or_die)
																{
																	cout << Monster[b].Get_monster_card_name() << " is killed!!" << endl;
																	for (int c = 0; c < output_Monster.size(); c++) {
																		if (output_Monster[c].Get_monster_card_name() == Monster[b].Get_monster_card_name()) {
																			output_Monster.erase(output_Monster.begin() + c);
																		}
																	}
																	Monster.erase(Monster.begin()+b);
			
																}
																goto to_break_u;
															}
														}
													}
													cout << "error target!!!" << endl;
													goto start_u;
												}
											to_break_u:;
												break;
											case 1://shield val
												playCharacter[j].round_shield += s.value;
												cout << playCharacter[j].map_name << " shield " << s.value << " this turn" << endl;
												break;
											case 2://move val
												Map.move(playCharacter[j].map_name, s.value, output_Monster);
												Map.output(Monster);
												break;
											case 3://heal val
												if (playCharacter[j].round_hp > playCharacter[j].max_hp) { playCharacter[j].round_hp = playCharacter[j].max_hp; }
												cout << playCharacter[j].map_name << " heal " << s.value << ", now hp is " << playCharacter[j].round_hp << endl;
												break;
											}
										}
									}
									else
									{
										for (auto s : m.skill_below)
										{
											switch (s.type)
											{
											case 0://attack val
											start_d:;
												cout << "attack monster: ";
												cin >> monster_map_name;
												if (monster_map_name != '0')
												{
													if ('a' <= monster_map_name && monster_map_name <= 'z')
													{
														if (Map.distant(playCharacter[j].map_name, monster_map_name, s.range))//判斷攻擊距離是否足夠
														{
															int b = 0;
															bool find_monster = true;
															for (; b < Monster.size(); b++)
															{
																if (Monster[b].Get_monster_card_name() == monster_map_name)
																{
																	find_monster = true;
																	break;
																}
																find_monster = false;
															}
															if (find_monster)
															{
																int damage;
																if (s.value >= Monster[b].monster_current_shield)
																{
																	damage = s.value - Monster[b].monster_current_shield;
																}
																else
																{
																	damage = 0;
																}
																Monster[b].monster_current_hp -= damage;
																if (Monster[b].monster_current_hp <= 0) {
																	Monster[b].live_or_die = false;
																}
																Map.output(Monster);
																cout << playCharacter[j].map_name << " attack " << Monster[b].Get_monster_card_name() << " " << damage << " damage, " << Monster[b].Get_monster_card_name() << " shield " << Monster[b].monster_current_shield << ", " << Monster[b].Get_monster_card_name() << " remain " << Monster[b].monster_current_hp << " hp" << endl;
																if (!Monster[b].live_or_die)
																{
																		cout << Monster[b].Get_monster_card_name() << " is killed!!" << endl;
																		for (int c = 0; c < output_Monster.size(); c++) {
																			if (output_Monster[c].Get_monster_card_name() == Monster[b].Get_monster_card_name()) {
																				output_Monster.erase(output_Monster.begin() + c);
																			}
																		}
																		Monster.erase(Monster.begin() + b);
																}
																goto to_break_d;
															}
														}
													}
													cout << "error target!!!" << endl;
													goto start_d;
												}
											to_break_d:;
												break;
											case 1://shield val
												playCharacter[j].round_shield += s.value;
												cout << playCharacter[j].map_name << " shield " << s.value << " this turn" << endl;
												break;
											case 2://move val
												Map.move(playCharacter[j].map_name, s.value, output_Monster);
												Map.output(Monster);
												break;
											case 3://heal val
												if (playCharacter[j].round_hp > playCharacter[j].max_hp) { playCharacter[j].round_hp = playCharacter[j].max_hp; }
												cout << playCharacter[j].map_name << " heal " << s.value << ", now hp is " << playCharacter[j].round_hp << endl;
												break;
											}
										}
									}
									for (int x = 0; x < playCharacter[j].hand_card.size(); x++)
									{
										if (playCharacter[j].hand_card[x].number == m.number)
										{
											playCharacter[j].hand_card[x].discard = true;
											playCharacter[j].discard_card_amount++;
										}
									}
								}
							}
						}
						else if (playCharacter[j].alive && playCharacter[j].long_rest)//若角色為長休狀態
						{
							cout << playCharacter[j].map_name << "'s turn: card -1" << endl;
							playCharacter[j].round_hp += 2;
							if (playCharacter[j].round_hp > playCharacter[j].max_hp) { playCharacter[j].round_hp = playCharacter[j].max_hp; }
							cout << playCharacter[j].map_name << " heal 2, now hp is " << playCharacter[j].round_hp << endl;
							cout << "remove card: ";
							cin >> card_numberTmp;
							for (auto c : playCharacter[j].hand_card)
							{
								if (c.number == card_numberTmp)
								{
									c.remove = true;
								}
								else
								{
									c.discard = false;
								}
							}
						}
					}
				}
				for (int j = 0; j < output_Monster.size(); j++) {
					if (output_Monster[j].round_order == i) {
						for (int k = 0; k < Monster.size(); k++) {
							if (Monster[k].monster_card_name == output_Monster[j].monster_card_name) {
								Monster[k].correct_card = output_Monster[j].correct_card;
								Monster[k].correct_card;
							}
						}
					}
				}
			}
			for (int s = 0; s < playCharacter.size(); s++) {
				for (int ss = 0; ss < Map.hero_char_name.size(); ss++) {
					if (playCharacter[s].map_name == Map.hero_char_name[ss])
					{
						if (Map.initalization_map(Map.hero_location_x[ss], Map.hero_location_y[ss])) {
							Map.output(Monster);
						}
					}
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
	inFile >> character_amount;//資料庫角色數量
	for (int i = 0; i < character_amount; i++)//讀取角色資料
	{
		character newCharacter;
		inFile >> newCharacter.name >> newCharacter.max_hp >> newCharacter.hand_card_amount;
		inFile >> newCharacter.total_card_amount;
		inFile.ignore();
		newCharacter.round_hp = newCharacter.max_hp;
		for (int j = 0; j < newCharacter.total_card_amount; j++)//讀取角色的每張卡片
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