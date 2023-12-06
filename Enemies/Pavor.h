#pragma once
#include "Enemy.h"
#include "../Castle/Tower.h"
#define k 1
class Pavor:public Enemy
{

public:
	Pavor(string R, Tower * t, int id, int FP, int T, double health, int P);
	virtual void Damage_to_Enemy(int fire_power_tower);
	virtual double PSE() ;
	~Pavor();
	virtual int Get_K() ;
	virtual void DecrementDist();
	virtual bool isShielded();
	void Fight(int TimeStep);
	
	
};

