#pragma once
#include"base.h"

class character
{
public:
	character();
	character(string newName, int newMax_hp, int newHand_card_amount, int newTotal_card_amount);

	string name = "";
	int max_hp = 0;
	vector<card> hand_card;//��P ��Ʈw���ϥ�
	int hand_card_amount = 0;//�i��Υd�P��
	vector<card> total_card;//�Ҧ��d�P
	int total_card_amount = 0;//���ͪ��`�@�����d�P�ƶq
};