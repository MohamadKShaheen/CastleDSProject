#pragma once
#include"Enemy.h"
#include "../Castle/Tower.h"
#define k 2
class Shielded:public Enemy
{

	double Priority;


public:
	Shielded(string R, Tower * t, int id, int FP, int T, double health, int P);
	virtual void Damage_to_Enemy(int fire_power_tower);
	double PSE();  //priority shielded enemy
	~Shielded();
	virtual bool isShielded();
	virtual int Get_K();
	virtual void DecrementDist();
	virtual void Fight(int TimeStep);
	
};

