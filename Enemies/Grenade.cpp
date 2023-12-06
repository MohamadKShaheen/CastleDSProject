#include "Grenade.h"



Grenade::Grenade(string R, Tower * t, int id, int FP, int T, double health, int P) : Enemy(R, t, id, FP, T, health, P)
{
	Clr = GREEN;
}


Grenade::~Grenade()
{
}

void Grenade::Damage_to_Enemy(int fire_power_tower) {
	Damage = (1 / (double)Distance)*(fire_power_tower);
	Health -= Damage;
	if (Health < 0)
	{
		Health = 0;
	}
}
double Grenade::PSE()
{
	return 0;
}
int Grenade::Get_K()
{
	return 1;
}

void Grenade::DecrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}

bool Grenade::isShielded()
{
	return false;
}

void Grenade::Fight(int TimeStep)
{
	// if the enemy i near by its tower it will shot the tower with 
	//the summation of the shielded enemies's firepowers and will die after that 
	float D = 0;
	Enemy* ptr = NULL;
	if (Distance == 3) {
		t->SetHealth(0);
		Health = 0;
	}
	else if (Distance != t->getUnPaved() + 1) {  //shaheen , waleed , salma œ»· Õ”»Ì «··Â Ê‰⁄„ «·ÊﬂÌ· ·« «·Â «·« «··Â number 2
		if (Arrival != TimeStep)//check if enemy arrived in the time step (i+1)(current timestep) not decrement distance of enemy and setting it in distance of 60 not 59
		{
			Distance--;
		}
	}

}
