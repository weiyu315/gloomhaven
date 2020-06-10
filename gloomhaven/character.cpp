#include"character.h"

character::character()
{
	this->name.clear();
	this->max_hp = 0;
	this->total_card_amount = 0;
	this->hand_card_amount = 0;
	this->locate_x = 0;
	this->locate_y = 0;
}
character::character(string newName, int newMax_hp, int newHand_card_amount, int newTotal_card_amount)
{
	this->name = newName;
	this->max_hp = newMax_hp;
	this->hand_card_amount = newHand_card_amount;//取得手牌個數
	//this->hand_card.resize(this->hand_card_amount);
	this->total_card_amount = newTotal_card_amount;//取得總共牌數
	//this->total_card.resize(this->total_card_amount);
}
bool character::setUsing_card(int index, int newUsing_card_number, card newUsing_card[2], vector<card> newHand_card)
{
	int i = 0;
	bool exist = true;
	while (newHand_card[i].number != newUsing_card_number)
	{
		i++;
		if (i >= newHand_card.size())
		{
			exist = false;
			cout << "Warning: Card number isn't exist in hand card!! Input again." << endl;
			return false;
		}
	}
	newUsing_card[index] = newHand_card[i];
	return true;
}
