#include "Pavor.h"



Pavor::Pavor(string R, Tower * t, int id, int FP, int T, double health, int P) :Enemy(R,t, id, FP, T, health, P)
{
	Clr = DARKBLUE;
}

void Pavor::Damage_to_Enemy(int fire_power_tower)
{
	Damage = (1 / (double)Distance)*(fire_power_tower);
	Health -= Damage;
	if (Health < 0)
	{
		Health = 0;
	}
}

double Pavor::PSE()
{
	return 0;
}


Pavor::~Pavor()
{
}

int Pavor::Get_K()
{
	return 1;
}

void Pavor::DecrementDist()
{
	if (Distance > MinDistance)
		Distance -= Firepower;
}

bool Pavor::isShielded()
{
	return false;
}

void Pavor::Fight(int TimeStep)
{
	//paved 
	if (t->getUnPaved() < Distance - 1)
	{
		if (TimeStep % (Period + 1) == 1 || TimeStep == 1||Period==0)
		{
			Distance -= Firepower;
			if (Distance < 3)
				Distance = 3;
			if (t->getUnPaved() >= Distance)
				t->setUnPaved(Distance - 1);
		}
		else
			Distance--;
	}
	//unpaved 
	else
	{
		if (TimeStep % (Period + 1) == 1||Period==0)//not reload time 
		{
			Distance -= Firepower;
			if (Distance < 3)
				Distance = 3;
			if (t->getUnPaved() >= Distance)
				t->setUnPaved(Distance - 1);
		}
	}
}
