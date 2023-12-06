#include "Shielded.h"



Shielded::Shielded(string R, Tower * t, int id, int FP, int T, double health, int P) :Enemy(R,t, id, FP, T, health, P)
{
	Clr = ORANGERED;
}



void Shielded::Damage_to_Enemy(int fire_power_tower)
{
	Damage = (1 / (double)Distance)*fire_power_tower*(0.5);
	Health -= Damage;
	if (Health < 0) 
	{
		Health = 0;
	}
}

double Shielded::PSE()
{
	Priority = ((Firepower / Distance)*C1) + (C2 / (remaining_to_shoot + 1)) + (Health*C3);
	return Priority;
}


Shielded::~Shielded()
{
}

bool Shielded::isShielded()
{
	return true;
}

int Shielded::Get_K()
{
	return 2;
}

void Shielded::DecrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}
void Shielded::Fight(int TimeStep)
{
	
		if (TimeStep % (Period + 1) == 0) {
			t->SetHealth(t->GetHealth() - ((double)k / Distance)*Firepower);
			if (t->GetHealth() < 0)
			{
				t->SetHealth(0);
			}
		}
		if (Distance != t->getUnPaved() + 1)  //double œ»· Õ”»Ì «··Â Ê‰⁄„ «·ÊﬂÌ· ·« «·Â «·« «··Â number 2
			if (Arrival != TimeStep)//check if enemy arrived in the time step (i+1)(current timestep) not decrement distance of enemy and setting it in distance of 60 not 59
			{
				Distance--;
			}
	
}
