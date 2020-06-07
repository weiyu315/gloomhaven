#pragma once
#include"base.h"

class character
{
public:
	character();
	character(string newName, int newMax_hp, int newHand_card_amount, int newTotal_card_amount);

	string name = "";
	int max_hp = 0;

	vector<card> total_card;//�Ҧ��d�P
	int total_card_amount = 0;//���ͪ��`�@�����d�P�ƶq

	vector<card> hand_card;//��P ��Ʈw���ϥ�
	int hand_card_amount = 0;//�i��Υd�P��

	card using_card[2] = {};//���b�ϥΪ���i�P
	void setUsing_card(int index, int newUsing_card_number, card newUsing_card[2], vector<card> newHand_card);

	int locate_x = 0;
	int locate_y = 0;
	string map_name = "";//�b�a�ϤW��ܪ��W�r A�BB�BC����

	bool long_rest = false;
	int round_dex = 0;//�����ӱ���
	int round_hp = 0;//������q
	vector<card> discard_card;//��P��
};