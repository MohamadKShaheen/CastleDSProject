#include "Jumper.h"



Jumper::Jumper(string R, Tower * t, int id, int FP, int T, double health, int P): Enemy(R, t, id, FP, T, health, P)
{
	Clr = WHITESMOKE;
}

void Jumper::Damage_to_Enemy(int fire_power_tower)
{
	Damage = (1 / (double)Distance)*fire_power_tower*(0.5);
	Health -= Damage;
	if (Health < 0)
	{
		Health = 0;
	}
}

double Jumper::PSE()
{
	return 0.0;
}

int Jumper::Get_K()
{
	return 1;
}

void Jumper::DecrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}


bool Jumper::isShielded()
{
	return false;
}

void Jumper::Fight(int TimeStep)
{
	if (TimeStep % (Period + 1) == 0) {
		t->SetHealth(t->GetHealth() - (1.0*k / Distance)*Firepower);
		if (t->GetHealth() < 0)
		{
			t->SetHealth(0);
		}
	}
	if (Distance > 3)  //shaheen , waleed , salma œ»· Õ”»Ì «··Â Ê‰⁄„ «·ÊﬂÌ· ·« «·Â «·« «··Â number 2
		if (Arrival != TimeStep)//check if enemy arrived in the time step (i+1)(current timestep) not decrement distance of enemy and setting it in distance of 60 not 59
		{
			Distance--;
		}
}

Jumper::~Jumper()
{
}
