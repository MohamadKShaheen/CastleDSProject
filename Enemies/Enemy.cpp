#include "Enemy.h"


Enemy::Enemy(string R,Tower* t1,int id, int FP, int T, double health, int P)
{
	setregion(R);
	t = t1;
	set_ID( id);
	set_fire_power( FP);
	set_Arrival_time(T);
	set_health(health);
	set_reload_time(P);
	SetDistance(60);
	remaining_to_shoot = 0;
	T_First = 0;
	Damage = 0;
}

Enemy::~Enemy()	
{
}

color Enemy::GetColor() const
{
	return Clr;
}

REGION Enemy::GetRegion() const
{
	return Region;
}

void Enemy::set_health(double H)
{
	Health = (H > 0) ? H : 0;
}

double Enemy::get_health()
{
	return Health;
}


void Enemy::set_Arrival_time(int time)
{
	Arrival = (time > 0) ? time : 1;
}

int Enemy::Get_Arrival_time()
{
	return Arrival;
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Enemy::GetDistance() const
{
	return Distance;
}

void Enemy::setregion(string R)
{
	if (R == "A")
	{
		Region = A_REG;
	}
	else if(R == "B")
	{
		Region = B_REG;
	}
	else if (R == "C")
	{
		Region = C_REG;
	}
	else if (R == "D")
	{
		Region = D_REG;
	}
}

void Enemy::set_reload_time(int t)
{
	Period = t;
}

int Enemy::get_reload_time()
{
	return Period;
}

void Enemy::set_fire_power(double fp)
{
	Firepower = fp;
}

double Enemy::get_fire_power()
{
	return Firepower;
}

void Enemy::set_ID(int id)
{
	ID = (id > 0) ? id : 1;
}

int Enemy::Get_ID()
{
	return ID;
}

void Enemy::Set_T_First(int F)
{
		T_First = F;
}

int Enemy::Get_T_First()
{
	return T_First;
}

void Enemy::Set_First_shot()
{
	First_shoot = T_First - Arrival;
}

int Enemy::get_First_shot()
{
	return First_shoot;
}

void Enemy::Set_T_Killed(int k)
{
	T_Killed = k;
}

int Enemy::Get_T_Killed()
{
	return T_Killed;
}

void Enemy::Set_Kill_Delay()
{
	Kill_Delay = T_Killed - T_First;
}

int Enemy::get_Kill_Delay()
{
	Set_Kill_Delay();
	return Kill_Delay;
}

void Enemy::Set_Life_Time()
{
	Life_time = T_Killed - Arrival;
}

int Enemy::Get_Life_Time()
{
	Set_Life_Time();
	return Life_time;
}


int Enemy::set_remaining()
{
	remaining_to_shoot--;
	if (remaining_to_shoot < 0)
		remaining_to_shoot = Period;
	return remaining_to_shoot;
}

Tower*& Enemy::GetTower()
{
	return t;
}

void Enemy::setConsts(double x, double y, double z)
{
	C1 = x;
	C2 = y;
	C3 = z;
}


double Enemy::C1 = 0;
double Enemy::C2 = 0;
double Enemy::C3 = 0;

void Enemy::setTower(Tower * g)
{
	t = g;
}

void Enemy::setReg(REGION o)
{
	Region = o;
}

