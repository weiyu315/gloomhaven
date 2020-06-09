#include"base.h"

skill::skill()
{
	this->type = -1;
	this->value = -1;
	this->range = 0;
}
skill::skill(string newSkill_name, int newVal)
{
	this->set_skill(newSkill_name, newVal);
}
skill::skill(int newType, int newVal)
{
	if (newType >= 0 && newType <= 3)
	{
		this->type = newType;
		this->value = newVal;
	}
	else
	{
		cout << "Warning:skill_type error." << endl;
	}
}
void skill::set_skill(string newSkill_name, int newVal)
{
	if (newSkill_name == "attack")
	{
		this->type = 0;
	}
	else if (newSkill_name == "shield")
	{
		this->type = 1;
	}
	else if (newSkill_name == "move")
	{
		this->type = 2;
	}
	else if (newSkill_name == "heal")
	{
		this->type = 3;
	}
	else
	{
		this->type = -1;
		return;
	}
	this->value = newVal;
}
/*-----------------------------------------------*/
card::card()
{
	skill_above.clear();
	skill_below.clear();
}
card::card(int newNumber, int newDex, vector<skill> newSkill_above, vector<skill> newSkill_below)
{
	this->number = newNumber;
	this->dex = newDex;
	this->skill_above.assign(newSkill_above.begin(), newSkill_above.end());
	this->skill_below.assign(newSkill_below.begin(), newSkill_below.end());
}
card::~card()
{
	this->skill_above.clear();
	this->skill_below.clear();
	this->dex = -1;
	this->number = -1;
	this->up = true;
}
