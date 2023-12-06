#pragma once
#include "Enemy.h"
#include "../Castle/Tower.h"
#define k 2

class Jumper : public Enemy
{
public:
	Jumper(string R, Tower * t, int id, int FP, int T, double health, int P);
	virtual void Damage_to_Enemy(int fire_power_tower);
	virtual double PSE();
	virtual int Get_K();
	virtual void DecrementDist();
	virtual bool isShielded();
	virtual void Fight(int TimeStep);
	~Jumper();
};

