#include"character.h"

character::character()
{
	this->name.clear();
	this->max_hp = 0;
	this->total_card_amount = 0;
	this->hand_card_amount = 0;
}
character::character(string newName, int newMax_hp, int newHand_card_amount, int newTotal_card_amount)
{
	this->name = newName;
	this->max_hp = newMax_hp;
	this->hand_card_amount = newHand_card_amount;//���o��P�Ӽ�
	//this->hand_card.resize(this->hand_card_amount);
	this->total_card_amount = newTotal_card_amount;//���o�`�@�P��
	//this->total_card.resize(this->total_card_amount);
}

